#include <stdio.h>
#include <zconf.h>

int issue_git_command(char * git_command[]){
    int fr = fork();

    if (fr > 0){
        execv("/bin/git", git_command);
        return -1;
    }
    else if (fr < 0) return -1;
    else return 1;
}
int main() {
    char * git_commit_command[] = {"git", "commit", "-m", "\"autocommit\""};
    if (issue_git_command(git_commit_command) < 0) printf("%s", "error");
    return 0;
}