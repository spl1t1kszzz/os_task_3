#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void a(const char *path) {
    if ((mkdir(path, 0777)) == -1) {
        perror("Error in a)");
        exit(-1);
    }
}

void b(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Error ib b)");
        exit(-11);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
}

void c(const char *path) {
    if (remove(path) == -1) {
        perror("Error in c");
        exit(-1);
    }
}

void d(const char *path) {
    FILE *file;
    if ((file = fopen(path, "w")) == NULL) {
        fclose(file);
        perror("Error in d)");
        exit(-1);
    }
    fclose(file);
}

void e(const char *path) {
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        fclose(file);
        perror("Error in e)");
        exit(-1);
    }
    char symbol;
    while ((symbol = (char) fgetc(file)) != EOF) {
        printf("%c", symbol);
    }
    fclose(file);
}

void f(const char *path) {
    if (remove(path) == -1) {
        perror("Error in f)");
        exit(-1);
    }
}

void g(const char *path) {
    if ((symlink(path, "symlink")) == -1) {
        perror("Error in g)");
        exit(-1);
    }
}

void h(const char *path) {
    char *buffer = (char *) calloc(4096, sizeof(char));
    if ((readlink(path, buffer, 4096)) == -1) {
        free(buffer);
        perror("Error in h)");
        exit(-1);
    }
    puts(buffer);
    free(buffer);
}

void i(const char *path) {
    char *buffer = (char *) calloc(4096, sizeof(char));
    if ((readlink(path, buffer, 4096)) == -1) {
        free(buffer);
        perror("Error in i) (readlink)");
        exit(-1);
    }
    FILE *file;
    if ((file = fopen(buffer, "r")) == NULL) {
        free(buffer);
        fclose(file);
        perror("Error in i) (open file)");
        exit(-1);
    }
    char symbol;
    while ((symbol = (char) fgetc(file)) != EOF) {
        printf("%c", symbol);
    }
    fclose(file);
    free(buffer);
}

void j(const char *path) {
    if ((remove(path)) == -1) {
        perror("Error in j)");
        exit(-1);
    }
}

void k(const char *path) {
    if ((link(path, "hard")) == -1) {
        perror("Error in k)");
        exit(-1);
    }
}

void l(const char *path) {
    if ((unlink(path)) == -1) {
        perror("Error in l)");
        exit(-1);
    }
}

void m(const char *path) {
    struct stat file_stat_struct;
    if ((stat(path, &file_stat_struct) == -1)) {
        perror("Error in m)");
        exit(-1);
    }
    printf((S_ISDIR(file_stat_struct.st_mode)) ? "d" : "-");
    printf((file_stat_struct.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat_struct.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat_struct.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat_struct.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat_struct.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat_struct.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat_struct.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat_struct.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat_struct.st_mode & S_IXOTH) ? "x   " : "-   ");
    printf("%d", file_stat_struct.st_nlink);

}

void n(const char *path) {
    if ((chmod(path, 0777) == -1)) {
        perror("Error in n)");
        exit(-1);
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }
    if (strcmp(argv[0], "./subtask_2_a") == 0) {
        a(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_b") == 0) {
        b(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_c") == 0) {
        c(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_d") == 0) {
        d(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_e") == 0) {
        e(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_f") == 0) {
        f(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_g") == 0) {
        g(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_h") == 0) {
        h(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_i") == 0) {
        i(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_j") == 0) {
        j(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_k") == 0) {
        k(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_l") == 0) {
        l(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_m") == 0) {
        m(argv[1]);
    } else if (strcmp(argv[0], "./subtask_2_n") == 0) {
        n(argv[1]);
    }
    return 0;
}
