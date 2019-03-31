#include <stdio.h>
#include <zconf.h>
#include <time.h>
#include <wait.h>

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
    char * git_push_command[] = {"git", "push", "origin", "master"};

    int commit_or_push =0; //commit = 0; push = 1;

    for(;;) {
        wait(5000);
        if (!commit_or_push)
            if (issue_git_command(git_commit_command) > 0) {
                commit_or_push = 1;
                continue;
            }
            else break;
        else{
            if (issue_git_command(git_push_command) > 0){
                commit_or_push = 0;
                continue;
            }
            else break;
        }

    }
    printf("%s", "something went wrong");
    return 0;
}