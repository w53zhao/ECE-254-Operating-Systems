#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

#define STRLEN1 128
#define STRLEN2 64

int main( int argc, char *argv[] ) {
	
	DIR *p_dir;
	struct dirent *p_dirent;
	
	char perm[] = "----------\0";
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;
	struct tm *tm;
	char month[4];
	char date[3];
	char hour[3];
	char minute[3];
	int size;
	char path[256];
	char *link;
	ssize_t r;
	char file[256];

	if( argc != 3 ) {
		printf("Usage: myls OPTION DIRECTORY\n");
		exit(1);
	}

	else {

		if( ( p_dir = opendir(argv[2]) ) == NULL ) {
			printf("Could not open (%s)\n", argv[2]);
			exit(1);
		}

		else {
	
			while( (p_dirent = readdir(p_dir)) != NULL ) {
										
				// create path string
				char *str_path = p_dirent -> d_name;	
				strcpy(path, "");
				strcat(path, argv[2]);
				
				// if user doesn't include '/' at end of directory name
				if( argv[2][strlen(argv[2]) - 1] != 47 ) {
					strcat(path, "/");
				}
				
				strcat(path, str_path);
				
				strcpy(file, "");	
				strcat(file, str_path);
	
				if( lstat( path, &buf ) < 0 ) {
					perror("lstat error");
					continue;
				}				
				
				mode_t mode = buf.st_mode;
				
				// get permissions
				perm[1] = ( mode & S_IRUSR ) ? 'r' : '-';
				perm[2] = ( mode & S_IWUSR ) ? 'w' : '-';
				perm[3] = ( mode & S_IXUSR ) ? 'x' : '-';
				perm[4] = ( mode & S_IRGRP ) ? 'r' : '-';
				perm[5] = ( mode & S_IWGRP ) ? 'w' : '-';
				perm[6] = ( mode & S_IXGRP ) ? 'x' : '-';
				perm[7] = ( mode & S_IROTH ) ? 'r' : '-';
				perm[8] = ( mode & S_IWOTH ) ? 'w' : '-';
				perm[9] = ( mode & S_IXOTH ) ? 'x' : '-';

				// get file type
				if ( S_ISREG(mode) ) perm[0] = '-';
				else if ( S_ISDIR(mode) ) perm[0] = 'd';
				
				#ifdef S_ISLNK
				else if ( S_ISLNK(mode) ) {
					perm[0] = 'l';
					
					// get target of link
					strcat(file, " -> ");

					link = malloc(buf.st_size + 1);
					r = readlink(path, link, buf.st_size + 1);

					strcat(file, link);
				}
				#endif
					
				else perm[0] = '?';
			
				if( stat( path, &buf ) < 0 ) {
					perror("stat error");
					continue;
				}
				
				// get user, group, filesize
				pwd = getpwuid(buf.st_uid);
				grp = getgrgid(buf.st_gid);
				size = (intmax_t)buf.st_size;		

				// get time based on argv[1]
				if( strcmp( argv[1], "-u") == 0 ) {
					tm = localtime(&buf.st_atime);
				}

				else if( strcmp( argv[1], "-c" ) == 0 ) {
					tm = localtime(&buf.st_ctime);
				}
				
				else if( strcmp( argv[1], "-l" ) == 0 ) {
					tm = localtime(&buf.st_mtime);
				}

				else {
					printf("OPTION [-u, -c, -l]\n");
					exit(1);
				}

				strftime(month, sizeof(month), "%b", tm);
				strftime(date, sizeof(date), "%d", tm);
				if( date[0] == '0' ) {
					date[0] = date[1];
					date[1] = date[2];
				}	
				
				strftime(hour, sizeof(hour), "%H", tm);
				strftime(minute, sizeof(minute), "%M", tm);

   				printf("%-12s %-10s %-10s %8d %-3s %2s %s:%s %s\n", perm, pwd -> pw_name, grp -> gr_name, size, month, date, hour, minute, file);
			}

			exit(0);
		}

	}

}
