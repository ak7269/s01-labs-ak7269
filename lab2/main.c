#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#define BUFFSIZ 200;
static int err_code;

/*
 * here are some function signatures and macros that may be helpful.
 */

void handle_error(char* fullname, char* action);
bool test_file(char* pathandname);
bool is_dir(char* pathandname);
//const char* ftype_to_str(mode_t mode);
void list_file(char* pathandname, char* name, bool list_long);
void list_dir(char* dirname, bool list_long, bool list_all, bool recursive);

/*
 * You can use the NOT_YET_IMPLEMENTED macro to error out when you reach parts
 * of the code you have not yet finished implementing.
 */
#define NOT_YET_IMPLEMENTED(msg)                  \
    do {                                          \
       printf("Not yet implemented: " msg "\n"); \
	    exit(255);    \             } while (0)  

/*
 * PRINT_ERROR: This can be used to print the cause of an error returned by a
 * system call. It can help with debugging and reporting error causes to
 * the user. Example usage:
 *     if ( error_condition ) {
 *        PRINT_ERROR();
 *     }
 */



#define NO_DIR(msg)   \
 do {                                          \
	 err_code=0x81;                                \
         printf("No such directory! : " msg "\n"); \
 } while (0) 

#define NO_RECUR(msg)   \
 do {                                          \
        printf("Recursion: not working " msg "\n"); \
        err_code=130;                                \
    } while (0)

#define NO_SpecifiedFile(msg)   \
 do {                                          \
        printf("File does not exist: " msg "\n"); \
        err_code=131;                                \
    } while (0)


#define NO_FILE(msg)   \
 do {                                          \
        printf("No such file! : " msg "\n"); \
        err_code=0x80;                                \
    } while (0)

#define NO_UName(msg)   \
 do {                                          \
        printf("No username and group name present " msg "\n"); \
        err_code=132;                                \
    } while (0)



#define PRINT_ERROR(progname, what_happened, pathandname)               \
    do {                                                                \
        printf("%s: %s %s: %s\n", progname, what_happened, pathandname, \
               strerror(errno));                                        \
    } while (0)

/* PRINT_PERM_CHAR:
 * This will be useful for -l permission printing.  It prints the given
 * 'ch' if the permission exists, or "-" otherwise.
 * Example usage:
 *     PRINT_PERM_CHAR(sb.st_mode, S_IRUSR, "r");
 */

#define PRINT_PERM_CHAR(mode, mask, ch) printf("%s", (mode & mask) ? ch : "-");

/*
 * Get username for uid. Return 1 on failure, 0 otherwise.
 */
//static int uname_for_uid(uid_t uid, char* buf, size_t buflen) {
//    struct passwd* p = getpwuid(uid);
//    if (p == NULL) {
//        return 1;
//    }
//    strncpy(buf, p->pw_name, buflen);
//    return 0;
//}

/*
 * Get group name for gid. Return 1 on failure, 0 otherwise.
 */
//static int group_for_gid(gid_t gid, char* buf, size_t buflen) {
//    struct group* g = getgrgid(gid);
//    if (g == NULL) {
//        return 1;
//    }
//    strncpy(buf, g->gr_name, buflen);
 //   return 0;
//}

/*
 * Format the supplied `struct timespec` in `ts` (e.g., from `stat.st_mtim`) as a
 * string in `char *out`. Returns the length of the formatted string (see, `man
 * 3 strftime`).
 */
//static size_t date_string(struct timespec* ts, char* out, size_t len) {
//    struct timespec now;
 //   timespec_get(&now, TIME_UTC);
 //   struct tm* t = localtime(&ts->tv_sec);
//    if (now.tv_sec < ts->tv_sec) {
        // Future time, treat with care.
//        return strftime(out, len, "%b %e %Y", t);
//   } else {
//      time_t difference = now.tv_sec - ts->tv_sec;
//      if (difference < 31556952ull) {
//         return strftime(out, len, "%b %e %H:%M", t);
//      } else {
//
//         return strftime(out, len, "%b %e %Y", t);
//     }
//  }
//}

/*
 * Print help message and exit.
 */
static void help() {
    /* TODO: add to this */
  printf("ls: List files\n");
  printf("\t--help: Print this help\n");
  printf("Flag -a will help to print the hidden files and files beginning with ."); 
  printf("Flag -l print more information on the files and subdirectories");
  printf("Flag -R to print the names of the files and subdirectories recursively");  
  printf("./ls prints the files and subdirectories in the current directory");
  exit(0);
}

/*
 * call this when there's been an error.
 * The function should:
 * - print a suitable error message (this is already implemented)
 * - set appropriate bits in err_code
 */
void handle_error(char* what_happened, char* fullname) {
    PRINT_ERROR("ls", what_happened, fullname);


    // TODO: your code here: inspect errno and set err_code accordingly.

    //if(errno==)
    return;
}

/*
 * test_file():
 * test whether stat() returns successfully and if not, handle error.
 * Use this to test for whether a file or dir exists
 */
bool test_file(char* pathandname) {
    struct stat sb;
    if (stat(pathandname, &sb)) {
        handle_error("cannot access", pathandname);
        return false;
    }
    return true;
}

/*
 * is_dir(): tests whether the argument refers to a directory.
 * precondition: test_file() returns true. that is, call this function
 * only if test_file(pathandname) returned true.
 */
bool is_dir(char* pathandname) {
    /* TODO: fillin */
	bool ans=test_file(pathandname);
	if(ans==true)//precondtion 
	{
		DIR* direc;
		if ((direc = opendir(pathandname))) {
			closedir(direc);
			return true;
	} 
	 if (ENOENT == errno) {
   		return false;
	} 
	 else {
   		return false;
	 }
	}

    return false;
}

/* convert the mode field in a struct stat to a file type, for -l printing */
//const char* ftype_to_str(mode_t mode) {
    /* TODO: fillin */
	
 //   return "?";
//}

/* list_file():
 * implement the logic for listing a single file.
 * This function takes:
 *   - pathandname: the directory name plus the file name.
 *   - name: just the name "component".
 *   - list_long: a flag indicated whether the printout should be in
 *   long mode.
 *
 *   The reason for this signature is convenience: some of the file-outputting
 *   logic requires the full pathandname (specifically, testing for a directory
 *   so you can print a '/' and outputting in long mode), and some of it
 *   requires only the 'name' part. So we pass in both. An alternative
 *   implementation would pass in pathandname and parse out 'name'.
 */
void list_file(char* pathandname, char* name, bool list_long) {
    /* TODO: fill in*/

//if(ans==true){
//printf("%s\n",name)strtok(dirname,"/");

 if(list_long==true){
  DIR *direc;
  struct stat   stbuf;
  struct passwd  *pwdd;
  struct group  *g;
  

  if(strcmp(pathandname,"lab2")==0)
                 pathandname="./";

  direc= opendir(pathandname);
  char buffe[BUFSIZ];
  snprintf(buffe,BUFSIZ,"%s/%s", pathandname, name);
  stat(buffe,&stbuf);

  if((stbuf.st_mode & S_IFMT) == S_IFDIR)
	printf("d ");
  else if((stbuf.st_mode & S_IFMT) == S_IFDIR)
	 printf("-"); 
  else
	printf("? ");	

  printf( (stbuf.st_mode & S_IRUSR) ? "r" : "-");
  printf( (stbuf.st_mode & S_IWUSR) ? "w" : "-");
  printf( (stbuf.st_mode & S_IXUSR) ? "x" : "-");
  printf( (stbuf.st_mode & S_IRGRP) ? "r" : "-");
  printf( (stbuf.st_mode & S_IWGRP) ? "w" : "-");
  printf( (stbuf.st_mode & S_IXGRP) ? "x" : "-");
  printf( (stbuf.st_mode & S_IROTH) ? "r" : "-");
  printf( (stbuf.st_mode & S_IWOTH) ? "w" : "-");                                                                                                                                                             printf( (stbuf.st_mode & S_IXOTH) ? "x" : "-");

  printf("\t%ld ", stbuf.st_nlink);

   pwdd = getpwuid(stbuf.st_uid);//username
   printf("\t%s ", pwdd->pw_name);

   g = getgrgid(stbuf.st_gid);//groupname
   printf("\t%s ", g->gr_name);

   printf("%zu",stbuf.st_size);
   printf("%s", ctime(&stbuf.st_mtime));
   printf("%s", name);

   printf("\n");
   closedir(direc);	
  }
else if(list_long==false)
    printf ("%s\n", name);
}

/* list_dir():
 * implement the logic for listing a directory.
 * This function takes:
 *    - dirname: the name of the directory
 *    - list_long: should the directory be listed in long mode?
 *    - list_all: are we in "-a" mode?
 *    - recursive: are we supposed to list sub-directories?
 */
void list_dir(char* dirname, bool list_long, bool list_all, bool recursive) {
    /* TODO: fill in
     *   You'll probably want to make use of:
     *       opendir()
     *       readdir()
     *       list_file()
     *       snprintf() [to make the 'pathandname' argument to
     *          list_file(). that requires concatenating 'dirname' and
     *          the 'd_name' portion of the dirents]
     *       closedir()
     *   See the lab description for further hints
     */
//	int i;	
//	for(i=2;i<strlen(dirname);i++)
//	{
//		if(dirname[i]=='/')
//			strtok(dirname,"/");
//
//	}
//	for(int j=i;j<strlen(dirname);j++)
//	{
//		if(dirname[j]=='/')
//			strtok(dirname,"/");
//	}//	strtok(dirname,"/");	
//

	if(recursive==true)
	{

  DIR *direct;
   struct dirent *dp;
	   list_dir(dirname, list_long, list_all,false);
     printf("\n");
    direct=opendir(dirname);
    if (direct != NULL) {

     while ((dp = readdir (direct)) != NULL){

        if(is_dir(dp->d_name)==true && strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0)
	       	list_dir(dp->d_name,list_long,list_all,false);
	else if(is_dir(dirname)==false)
	{
		NO_RECUR("");
	}
        }closedir (direct);
    }
    else{
	    NO_RECUR("");
    }








       // list_recur(dirname,list_long,list_all);
        return;
      }
	DIR *dir;
	struct dirent *ent;
	dir = opendir (dirname);
	//char buff[BUFSIZ]
	
	char* l="lab2";
         if (dir != NULL) 
	 {
      		printf("%s:\n",dirname);
		while ((ent = readdir (dir)) != NULL){
			char* s=ent->d_name;
			 if(ent->d_type==DT_REG && list_all==false){
				if( s[0]!='.')
				       	list_file(dirname,ent->d_name, list_long);
			 }
			else if (list_all==true)
			{
				list_file(dirname,ent->d_name, list_long);	
			}
		}closedir (dir);
		printf("\n");
	 	 
         }
	 else if(strcmp(dirname,l)==0){
		printf("%s:\n",dirname);
              	dir = opendir ("./");
		while ((ent = readdir (dir)) != NULL){
		
		 char* s=ent->d_name;
		 if(ent->d_type==DT_REG && list_all==false)
		 {
			if(s[0]!='.')
		 
			 list_file(dirname,ent->d_name, list_long);  
		 }
		 else if(list_all==true)
		 {
			 list_file(dirname,ent->d_name, list_long);	
		 }
	       	}closedir (dir);

		
             	printf("\n");
	 }
	
          else{
                /* Could not open directory */
          // fprintf (stderr, "Cannot open %s (%s)\n", dirname, strerror (errno));
                //  exit (EXIT_FAILURE)	
		
		if(is_dir(dirname)==false)
		{
			printf("%s",dirname);
	
			NO_DIR("directory not present");
		}
		else if(test_file(dirname)==false)
		{
			printf("%s",dirname);
			NO_FILE("file not present");

		}
		
		else if(recursive==true)
		{
		
		 	NO_RECUR("recursion flag does not work");
		}				

                else{
			NO_SpecifiedFile(".");
		
		}


             }
		 

}

int main(int argc, char* argv[]) {
    // This needs to be int since C does not specify whether char is signed or
    // unsigned.
    int opt;
    err_code = 0;
    bool list_long = false, list_all = false, recursive=false;
    // We make use of getopt_long for argument parsing, and this
    // (single-element) array is used as input to that function. The `struct
    // option` helps us parse arguments of the form `--FOO`. Refer to `man 3
    // getopt_long` for more information.
    struct option opts[] = {{.name = "help", .has_arg = 0, .flag = NULL, .val = '\a'}};

    // This loop is used for argument parsing. Refer to `man 3 getopt_long` to
    // better understand what is going on here.
    while ((opt = getopt_long(argc, argv, "1alR", opts, NULL)) != -1) {
        switch (opt) {
            case '\a':
                // Handle the case that the user passed in `--help`. (In the
                // long argument array above, we used '\a' to indicate this
                // case.)
                help();
                break;
            case '1':
                // Safe to ignore since this is default behavior for our version
                // of ls.
                break;
            case 'a':
                list_all = true;
                break;
                // TODO: you will need to add items here to handle the
                // cases that the user enters "-l" or "-R"
	    case 'l':
		list_long=true;
		break;
	    case 'R':
		recursive=true;
		break;
            default:
                printf("Unimplemented flag %d\n", opt);
                break;
        }
    }

    // TODO: Replace this.
    if(optind==argc){
     list_dir("./",list_long,list_all,recursive);
    }

    if(argc>1){
    for(int i=optind;i<argc;i++){
    list_dir(argv[i],list_long,list_all,recursive);
    }

    }
    if (optind < argc) {
        printf("Optional arguments: ");
    }
    for (int i = optind; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    if (optind < argc) {
        printf("\n");
    }

   // NOT_YET_IMPLEMENTED("Listing files");
    exit(err_code);
}

