#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

#define MAGIC_ENTRY_POINT 0x400000

static void report_error(const char *msg);

/*
 * 1. elf header
 * 2. program header
 * 3. str in text
 * 4. text
 * 5. section header is not needed
 * */

int main() {
    char str_in_text[] = "Hello, World\n";

    Elf64_Ehdr elf_header = {
        .e_ident = {
            ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,
            ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV, 0,
            0, 0, 0, 0, 0, 0, 0,
        },
        .e_type = ET_EXEC,
        .e_machine = EM_X86_64,
        .e_version = EV_CURRENT,
        .e_entry = MAGIC_ENTRY_POINT + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(str_in_text),
        .e_phoff = sizeof(Elf64_Ehdr),
        .e_shoff = 0,
        .e_flags = 0,
        .e_ehsize = sizeof(Elf64_Ehdr),
        .e_phentsize = sizeof(Elf64_Phdr),
        .e_phnum = 1,
        .e_shentsize = sizeof(Elf64_Shdr),
        .e_shnum = 0,
        .e_shstrndx = SHN_UNDEF,
    };

    uint8_t text[] = {
        0xb8, 0x01, 0x00, 0x00, 0x00,   // mov rax, 1
        0xbf, 0x01, 0x00, 0x00, 0x00,   // mov rdi, 1
        0x48, 0x8d, 0x34, 0x25,         // lea
        0x00, 0x00, 0x00, 0x00,         // [placeholder] the addr of str_in_text
        0xba,                           // mov rdx,
        0x00, 0x00, 0x00, 0x00,         // [placeholder] the length of str_in_text
        0x0f, 0x05,                     // syscall
        0xb8, 0x3c, 0x00, 0x00, 0x00,   // mov rax, 60
        0xbf, 0x00, 0x00, 0x00, 0x00,   // mov rdi, 0
        0x0f, 0x05,                     // syscall
    };
    *(uint32_t *)&text[14] = MAGIC_ENTRY_POINT + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr);
    *(uint32_t *)&text[19] = strlen(str_in_text);

    Elf64_Phdr prog_header = {
        .p_type = PT_LOAD,
        .p_flags = PF_R | PF_X,
        .p_offset = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr),
        .p_vaddr = MAGIC_ENTRY_POINT + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr),
        .p_paddr = 0,
        .p_filesz = sizeof(str_in_text) + sizeof(text),
        .p_memsz = sizeof(str_in_text) + sizeof(text),

        // NOTE: p_offset % p_align == p_vaddr % p_align
        .p_align = sysconf(_SC_PAGESIZE),  // get page size
    };

    int fd = open("./tiny_bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    if (fd == -1) {
        report_error("open file failed");
    }

    int len = write(fd, (void *)&elf_header, sizeof(elf_header));
    if (len != sizeof(elf_header)) {
        report_error("write elf header failed");
    }

    len = write(fd, (void *)&prog_header, sizeof(prog_header));
    if (len != sizeof(prog_header)) {
        report_error("write program header failed");
    }

    len = write(fd, str_in_text, sizeof(str_in_text));
    if (len != sizeof(str_in_text)) {
        report_error("write str_in_text failed");
    }

    len = write(fd, text, sizeof(text));
    if (len != sizeof(text)) {
        report_error("write text failed");
    }

    (void) close(fd);
    return 0;
}

void report_error(const char *msg) {
    perror(msg);
    exit(1);
}
