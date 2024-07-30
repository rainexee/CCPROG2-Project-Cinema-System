/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
<Juan Antonio Menchaca>, DLSU ID# <12110612>
<Elijah Raphael Murcia>, DLSU ID# <11901543>
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char String50[51];
typedef char String10[11];
typedef char String3[4];
typedef char String1000[1001];
typedef char showtime[8];

typedef struct {
  int CinemaNumber;
  String50 MovieTitle;
  String1000 MovieDescription;
  String50 RunningTime;  // can change string value
  showtime ShowTime[37]; // 6 cinemas = 6 * 6 + 1 null byte
} MovieData;

/// MODIFIED SEATINGDATA STRUCT -Eli
typedef struct {
  MovieData Connect;
  int seatArr[5][10];
  int Occupancy;
  showtime Timeslot;
  int currentTix;
} SeatingData;

typedef struct {
  int CinemaNumber;
  String50 MovieTitle;
  showtime Timeslot;
  String3 SeatNum;
} TicketInfo;

typedef struct {
  int ticketQuantity;
  TicketInfo cart[144];
} CustomerCart;

// Updated function prototypes
void preloadmovie(MovieData preload[]);
void SearchMovie(SeatingData s[][6], String50 MovieName);
void ViewSchedule(MovieData ScheduleView[]);
/// SEATING FUNCTION PROTOTYPES
void showSeating(SeatingData *c);
int vSeat(char r, int n);
//void SelectionSort(MovieData Movies[], int size);     UNUSED
void SelectCinemaSeat(MovieData Movies[], SeatingData Showings[][6],
                      CustomerCart *Cart);
void SeatSelect(SeatingData *c, CustomerCart *t);
void PrintCart(CustomerCart *Cart, SeatingData s[][6]);
void SaveAndExit(SeatingData s[][6]);

// LOAD NEW SCHEDULE FUNCTION PROTOTYPE
void loadschedule(SeatingData s[][6], MovieData Update[]);

/// INITIALIZATION FUNCTION PROTOTYPES
void initSeatingData(SeatingData Showings[][6], MovieData Movies[]);
void initCustomerCart(CustomerCart *myCart);

int main() {
  printf("Welcome to Rain's Theatre!\n\n");
  int decider = -1, exitflag = 1;

  int i;
  char d;
  char dChar[6] = {'1', '2', '3', '4', '5', '6'};
  int dInt[6] = {1, 2, 3, 4, 5, 6};

  String50 SearchMov;

  MovieData preload[7];
  SeatingData Seats[6][6];
  CustomerCart myCart;

  preloadmovie(preload);
  initSeatingData(Seats, preload);
  initCustomerCart(&myCart);

  while (exitflag == 1) {
    printf("\n Main Menu\n");
    printf("[1.] Search Movie\n");
    printf("[2.] View Schedules\n");
    printf("[3.] Seat Selection\n");
    printf("[4.] Print Ticket\n");
    printf("[5.]Load Schedule\n");
    printf("[6.] Save and Exit\n");
    printf("< ");
    scanf(" %s", &d);
    decider = -1;

    for(i = 0; i < 6; i++){if(d == dChar[i]){decider = dInt[i];}}

    switch (decider) {
    case 1:
      /*printf("Enter Movie Name\n >");
      scanf(" %50[^\n]",
            SearchMov); // Fixed to handle spaces and prevent overflow*/
      SearchMovie(Seats, SearchMov);
      break;
    case 2:
      ViewSchedule(preload);
      break;
    case 3:
      SelectCinemaSeat(preload, Seats, &myCart);
      break;
    case 4:
      // PrintTicket(MovieData preload[], int size);
      PrintCart(&myCart,
                Seats); /// FOR PROTOTYPING PURPOSES ONLY, SHOULD BE REMOVED
      break;
    case 5:
      loadschedule(Seats, preload);
      initSeatingData(Seats, preload);
      initCustomerCart(&myCart);
      break;
    case 6:
      // SaveAndExit(MovieData preload[], int size);
      SaveAndExit(Seats);
      exitflag = 0;
      break;
    default:
      printf("Invalid selection!\n");
    }
  }
}

// seating data for back end, MovieData for front end
/* loadschedule Manually loads the Movie Theatre Text file
@param s[][6] - Seating Data Struct that contains the import data for seat selection, etc. This is the back end design
@param Update[] - Struct in charge of showing the movie data, this is the front end design
@returns void
Pre-condition: Input must contain .txt at the end, and has to be in the same folder.
*/
void loadschedule(SeatingData s[][6], MovieData Update[]) {
  String50 filename;
  int i, j, k;
  showtime temp;
  printf("Enter Movie File with .txt\n >");
  scanf("%50s", filename);
  FILE *newfp = fopen(filename, "r");

  if (newfp == NULL) {
    printf("File does not exist!\n Enter file name \n >");
    scanf("%50s", filename);
  }
  for (i = 0; i < 6; i++) {
    fscanf(newfp, " %d", &s[i]->Connect.CinemaNumber);
    fscanf(newfp, " %50[^\n]", s[i]->Connect.MovieTitle);
    fscanf(newfp, " %1000[^\n]", s[i]->Connect.MovieDescription);
    fscanf(newfp, " %50s", s[i]->Connect.RunningTime);

    strcpy(Update[i].MovieTitle, s[i]->Connect.MovieTitle);
    strcpy(Update[i].MovieDescription, s[i]->Connect.MovieDescription);
    strcpy(Update[i].RunningTime, s[i]->Connect.RunningTime);
    for (j = 0; j < 6; j++) {
      if(getc(newfp) == EOF){
        Update[i+1].CinemaNumber = atoi(temp);
        for(k = j; k < 6; k++){
            strcpy(s[i]->Connect.ShowTime[k], "NULLSHO");
            strcpy(Update[i].ShowTime[j], s[i]->Connect.ShowTime[j]);
        }
        j = 5;
      }else{
        fscanf(newfp, " %7s", temp);
        if(strlen(temp) > 1){
            strcpy(s[i]->Connect.ShowTime[j], temp);
            strcpy(Update[i].ShowTime[j], s[i]->Connect.ShowTime[j]);
        }else if(strlen(temp) == 1){
            Update[i+1].CinemaNumber = atoi(temp);
            for(k = j; k < 6; k++){
                strcpy(s[i]->Connect.ShowTime[k], "NULLSHO");
                strcpy(Update[i].ShowTime[j], s[i]->Connect.ShowTime[j]);
            }
            j = 5;
        }
      }
    }
  }
  printf("new load Succeeded!\n");
  fclose(newfp);
}

/* preloadmovie - Loads the movie data into the program on startup
@param preload[] - MovieData struct where all the data goes in to.
@returns void
Pre-condition: File must exist, if File not found it will reprompt.
*/

void preloadmovie(MovieData preload[]) {
  FILE *fp = fopen("MovieSched5.txt", "r");
  String50 missingfile;
  showtime temp = "NULL";


  int i, j, k;
  if (fp == NULL) {
    printf("Schedule File Missing! \n Enter Movie Schedule filename\n >");
    scanf(" %50[^\n]s",
          missingfile); // Fixed to handle spaces and prevent overflow
    strcat(missingfile, ".txt");
    fp = fopen(missingfile,
               "r"); // Attempt to open the file again with the correct name
  }
  for (i = 0; i < 6; i++) {
    fscanf(fp, " %d", &preload[i].CinemaNumber);
    printf(" %d\n", preload[i].CinemaNumber);
    fscanf(fp, " %50[^\n]", preload[i].MovieTitle);
    fscanf(fp, " %1000[^\n]", preload[i].MovieDescription);
    fscanf(fp, " %50s", preload[i].RunningTime);
    for (j = 0; j < 6; j++) {
      if(getc(fp) == EOF){
        for(k = j; k < 6; k++){
            preload[i+1].CinemaNumber = atoi(temp);
            printf("i%d %d\n", i, preload[i].CinemaNumber);
            strcpy(preload[i].ShowTime[k], "NULLSHO");
        }
        j = 5;
      }else{
        fscanf(fp, " %7s", temp);
        if(strlen(temp) > 1){
            strcpy(preload[i].ShowTime[j], temp);
        }else if(strlen(temp) == 1){
            preload[i+1].CinemaNumber = atoi(temp);
            printf("i%d %d\n", i, preload[i].CinemaNumber);
            for(k = j; k < 6; k++){
                strcpy(preload[i].ShowTime[k], "NULLSHO");
            }
            j = 5;
        }
      }
    }
  }
  printf("Preload Succeeded!\n");
  fclose(fp);
}

/* loadschedule Manually loads the Movie Theatre Text file
@param s[][6] - Seating Data Struct that contains the import data for seat selection, etc. This is the back end design
@param Update[] - Struct in charge of showing the movie data, this is the front end design
@returns void
Pre-condition: Input must contain .txt at the end, and has to be in the same folder.
*/
void ViewSchedule(MovieData ScheduleView[]) {
  int i, j;
  for (i = 0; i < 6; i++) {
    printf("Cinema Number: %d\n", ScheduleView[i].CinemaNumber);
    printf("Movie Title: %s\n", ScheduleView[i].MovieTitle);
    printf("Movie Description: %s\n", ScheduleView[i].MovieDescription);
    printf("Running Time: %s\n", ScheduleView[i].RunningTime);
    for (j = 0; j < 6; j++) {
      if(strcmp(ScheduleView[i].ShowTime[j], "NULLSHO") != 0){
      printf("Show Times: %s\n", ScheduleView[i].ShowTime[j]);} // Fixed indexing
    }
  }
}

/* SortByTime - Sorts the movies based on time from earliest to latest
@param s[] - Seating Data Struct 
@param size = Size of the array index
@returns void
Pre-condition: There is data in s[].
*/
void SortByTime(SeatingData s[], int size) { // ind[0] = 1
  int i, j;
  int min;
  SeatingData temp;

  for (i = 0; i < size - 1; i++) {
    min = i;
    for (j = i + 1; j < size; j++) {
      if (strcmp(s[min].Timeslot, s[j].Timeslot) > 0) {
        min = j;
      }
    }
    if (min != i) {
      temp = s[i];
      s[i] = s[min];
      s[min] = temp;
    }
  }
}

/* PrintSearch - Prints out the search results
@param s[] - Seating Data Struct 
@param size = Size of the array index
@returns void
*/
void PrintSearch(SeatingData s[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf("\t\tMovie %d: %s\n", i + 1, s[i].Connect.MovieTitle);
    printf("\t\tSchedule: %s\n", s[i].Timeslot);
    printf("\t\tAvailable Seats: %d\n\n", 50 - s[i].Occupancy);
  }
}

/* SearchMovie - Searches Movies either by Title or Time
@param s[] - Seating Data Struct 
@param MovieName - String input to string compare against the list.
@returns void
Pre-condition: For Time Search: Inputs must be the hour ex: "7" or "10".
*/
void SearchMovie(SeatingData s[][6], String50 MovieName) {

  /// TO-DO: implement error handling of invalid string inputs
  ///          implement occupancy of each showtime
  String10 Time;
  String10 DorN = "PM"; // defaults the input time to PM since there are only 2
                        // possible AM hour inputs
  char tempTime[3];
  SeatingData tempSched[10];
  // int showInd[10]; unused variable
  int sIctr = 0;
  int schedCtr = 0;

  int i, j, k, l;
  int Choice = 0;
  char c;
  char cChar[2] = {'1', '2'};
  int cInt[2] = {1, 2};

  printf("Search by\n [1.] Movie Title \n [2.] Time\n >");
  scanf(" %s", &c);

  for(l = 0; l < 2; l++){if(c == cChar[l]){Choice = cInt[l];}}

  switch (Choice) {
  case 1:
    printf("Enter Movie Name: ");
    scanf(" %50[^\n]",
          MovieName);         // Fixed to he spaces and prevent overflow
    for (i = 0; i < 6; i++) { // Assuming 6 movies for consistency
      if (strcmp(MovieName, s[i][0].Connect.MovieTitle) == 0) {
        printf("Output: %s\n", s[i][0].Connect.MovieTitle);
        for (j = 0; j < 6;
             j++) { // for loop to show all show times for specified movie
          if (strlen(s[i][j].Timeslot) >= 1) {
            if(strcmp(s[i][j].Timeslot, "NULLSHO") != 0){
            printf("Showing %d: %s\n", j + 1, s[i][j].Timeslot);
            printf("Available Seats: %d\n\n", 50 - s[i][j].Occupancy);}
          }
        }
      }
    }
    break;
  case 2:
    printf("Enter Time: ");
    scanf(" %s", Time); // Fixed buffer size
    if (strcmp(Time, "10") == 0 || strcmp(Time, "11") == 0) {
      strcpy(DorN, "AM");
    }
    if (strlen(Time) == 1) {
      strcat(Time, ":");
      printf("\nMovies starting from %c:00%s to %c:59%s\n\n", Time[0], DorN,
             Time[0], DorN);
    } else {
      printf("\nMovies starting from %s:00%s to %s:59%s\n\n", Time, DorN, Time,
             DorN);
    }

    for (i = 0; i < 6; i++) { // Assuming 6 movies for consistency
      for (j = 0; j < 6; j++) {
        // assign the first two digits of the selected showtime's time to look
        // for a match
        for (k = 0; k < 2; k++) {
          tempTime[k] = s[i][j].Timeslot[k];
        }
        tempTime[2] = '\0';
        if (strcmp(tempTime, Time) == 0) {
          tempSched[schedCtr] = s[i][j];
          schedCtr++;
          // printf("This is showing number %d for %s\n", j+1,
          // s[i][j].Connect.MovieTitle);
          sIctr++; // showing index counter goes up
        }
      }
    }
    SortByTime(tempSched, schedCtr);
    PrintSearch(tempSched, schedCtr);
    break;
  default:
    printf("Invalid selection!\n");
  }
}


//UNUSED
/*
void SelectionSort(MovieData Movies[], int size) {
  int i, j, min;
  MovieData Temp;
  for (i = 0; i < size - 1; i++) {
    min = i;
    for (j = i + 1; j < size; j++) {
      // Sorting logic here, assuming it sorts based on a valid criterion
    }
    Temp = Movies[i];
    Movies[i] = Movies[min];
    Movies[min] = Temp;
  }
}
*/

/* showSeating - Displays Seating GUI and if seat is taken logic
@param *c = Seating Data Structure, Shows available seat and taken seat 
@returns void
Pre-condition:N/A.
*/

/// SEATING FUNCTIONS
void showSeating(SeatingData *c) {
  char letterArray[5] = {'A', 'B', 'C', 'D', 'E'};
  int i, j;

  for (i = 0; i < 6; i++) {
    if (i == 0) {
      printf(" ");
      for (j = 0; j < 39; j++) {
        printf("_");
      }
      printf("\n");
    } else if (i % 2 == 0 || i == 1) {
      printf("|");
      printf("%40c\n", '|');
    } else if (i < 5) {
      printf("|");
      printf("%24s%16c", "MOVIE SCREEN", '|');
      printf("\n");
    } else {
      printf("|");
      for (j = 0; j < 39; j++) {
        printf("_");
      }
      printf("|\n");
    }
  } /// PRINTING THE SCREEN

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 10; j++) {
      if (c->seatArr[i][j] != 11) { // seat indexes equal to 11 are taken
        printf(
            "|%c%d|", letterArray[i],
            c->seatArr[i][j]); // shows row letter and seat number if available
      } else {
        printf("| X|"); // X if the seat is taken
      }
    }
    printf("\n");
  }
}

/* initSeatArray - Initializes Seat Array
@param *Showings = Contains Seat Arrays
@returns void
Pre-condition:N/A.
*/
void initSeatArray(SeatingData *Showings) { /// INITIALIZES EACH SHOWING'S SEATING ARRAY
  int i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 10; j++) {
      Showings->seatArr[i][j] =
          j + 1; // initializes each seat index for current showing equal to the
                 // seat number
    }
  }
  Showings->Occupancy = 0; // initializes current showing occupancy to 0. should have a max of 50.
}

/* initSeatingData - Initializes all showings in the seatingdata 2d array.
@param Showings[][6] - Seating Data Structure. 
@param Movies[] - Movie Data Structure
@returns void
Pre-condition:N/A.
*/
void initSeatingData(SeatingData Showings[][6],  MovieData Movies[]) { /// INITIALIZES ALL SHOWINGS IN THE
                                           /// SEATINGDATA 2D ARRAY

  int i, j;
  int numShowtimes = 0; // keeps track of how many showtimes were initialized

  for (i = 0; i < 6; i++) {   // ROWS
    for (j = 0; j < 6; j++) { // columns
      Showings[i][j].currentTix = 0;
      Showings[i][j].Connect =
          Movies[i]; // each showing parent struct initialized with moviedata
                     // child struct, fetching its data
      initSeatArray(
          &Showings[i][j]); // each showing's seat arrangement is initialized
      strcpy(Showings[i][j].Timeslot,
             Movies[i].ShowTime[j]); // each showing's timeslot is initialized
                                     // using data from the movies struct array
      numShowtimes++;
    }
  }

  /// EVERYTHING BELOW THIS LINE IS FOR TRACING PURPOSES ONLY AND SHOULD BE
  /// DELETED SOON

  printf("All %d showtimes initialized.\n", numShowtimes);

  for (i = 0; i < 6; i++) { // ROWS
    printf("Time slots for %s \n", Showings[i][0].Connect.MovieTitle);
    printf("CINEMA NUMBER for %d \n", Movies[i].CinemaNumber);
    for (j = 0; j < 6; j++) { // columns
      printf("Showing %d: %s\n", j + 1, Showings[i][j].Timeslot);
    }
  }
}

/*initCustomerCart - Initializes the Cart of the customer
@param *myCart = pointer structure of the customers cart, MovieTitle, Cinema Number, Timeslots and seatnums are stored for 
                ticket printing purposes.
@returns void
Pre-condition:N/A.
*/
void initCustomerCart(CustomerCart *myCart) {
  int i;

  myCart->ticketQuantity = 0;
  for (i = 0; i < 144; i++) {
    myCart->cart[i].CinemaNumber = 0;
    strcpy(myCart->cart[i].MovieTitle, "NULL TITLE");
    strcpy(myCart->cart[i].Timeslot, "--:--");
    strcpy(myCart->cart[i].SeatNum, "");
  }
}

/*vSeat - Check if seat is Valid
@param r = Row of seat
@param n = Column of seat
@returns 1 if seat is confirmed valid, else returns 0

Pre-condition: user must have input a char and an int in seatSelect func
*/
int vSeat(char r,
          int n) { /// CHECKS SEAT VALIDITY FOR THE 'SelectCinemaSeat' FUNCTION
  if (r >= 'A' && r <= 'E') { // char input is only from A to E, corresponds to
                              // row in seatArr
    if (n >= 0 && n <= 9) {   // int input is only from 0 to 9, corresponds to
                              // column in seatArr
      return 1;
    }
  }
  return 0;
}

/*SelectCinemaSeat - Function where the user can choose a movie showtime to buy seats for
@param Movies[] - MovieData is stored here
@param Showings[][6] - SeatingData for customer 
@param *Cart - Customers chosen movies and seats are sent here to be printed out on a ticket.
@returns void
Pre-condition:N/A.
*/
void SelectCinemaSeat(MovieData Movies[], SeatingData Showings[][6],
                      CustomerCart *Cart) {
  int i, j, k;
  int exitflag = 1;
  int decider = 0;
  char input1, input2;
  char numchar[6] = {'1', '2', '3', '4', '5', '6'};
  int numint[6] = {1, 2, 3, 4, 5, 6};
  int movieIndex = -1;

  printf("Which movie would you like to watch? \n");
  while (exitflag == 1) {
    for (i = 0; i < 6; i++) {
      printf("[%d.] %50s\n", i + 1, Movies[i].MovieTitle);
    }

    scanf(" %s", &input1);
    for(k = 0; k < 6; k++){if(input1 == numchar[k]){movieIndex = numint[k] - 1;}}

    // view the schedules for the selected movie
    system("cls");
    if (movieIndex >= 0 && movieIndex <= 5) {
      // display showtimes
      printf("Displaying Showtimes for %s:\n\n", Movies[movieIndex].MovieTitle);
      for (j = 0; j < 6; j++) {
        if(strcmp(Movies[movieIndex].ShowTime[j], "NULLSHO") != 0){
        printf("Showing %d: %s\n", j + 1, Movies[movieIndex].ShowTime[j]);
        }
      }
      printf("Select a showing: ");
      scanf(" %s", &input2);

      for(k = 0; k < 6; k++){if(input2 == numchar[k]){decider = numint[k];}}

      switch(decider){
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
            if(strcmp(Showings[movieIndex][decider - 1].Timeslot, "NULLSHO") == 0){
                printf("Invalid selection! Try again.\n\n");
                exitflag = 1;
                break;
            }else{
                SeatSelect(&Showings[movieIndex][decider - 1], Cart);
                exitflag = 0;
                break;
            }
          default:
            printf("Invalid selection! Try again.\n\n");
            exitflag = 1;
      }
    } else {
      exitflag = 1;
    }
  }
}

/*SeatSelect - Customers pick their seat here
@param *c = Seating Data Structure, is required for Customer Cart *t
@param *t = Customer Cart structure, contains tickets etc.
@returns void
Pre-condition: Customer must have picked a valid movie with a valid showtime in SelectCinemaSeat
*/
void SeatSelect(SeatingData *c, CustomerCart *t) {

  char row = 'G';
  int rN;
  int num = -1;
  int validSeat = 0;
  int exitStatus = 0;
  char YorN;

  char letterArray[5] = {'A', 'B', 'C', 'D', 'E'};
  char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  String3 temp;

  int seatRow = 0;
  // int newLoop = 0; FOR TRACING PURPOSES ONLY

  if (c->currentTix >= 4) {
    printf("Max ticket allowance reached!\n\n");
  }

  if (c->Occupancy >= 50) {
    printf("Maximum occupancy reached!\n\n");
  }

  while (validSeat != 1 && exitStatus != 1 && c->currentTix < 4 && c->Occupancy < 50) {
    /*if(newLoop > 0){
        printf("LOOP %d\n", newLoop+1);
    }*/ ///THIS CODE IS PURELY FOR TRACING PURPOSES
    system("cls");
    printf("NOW SHOWING: %s at %s\n", c->Connect.MovieTitle, c->Timeslot);
    printf("NOTE: Seats marked with an X are already taken and thus cannot be "
           "selected.\n");

    showSeating(c);

    // reinitializing of values for every loop iteration
    row = 'G';
    rN = -1;
    num = -1;

    printf("\nInput the seat you would like\n");
    scanf(" %c%d", &row, &num);
    num--;
    printf("Your selected seat %c %d\n", row, num + 1);

    seatRow = vSeat(row, num); // checks seat validity

    if (seatRow == 1) {
      for (int i = 0; i < 5; i++) {
        if (row == letterArray[i]) {
          rN = i;
        }
      } // converts the char into a number that corresponds to row number in the
        // seatArr

      // conditionals to check for seats taken
      if (c->seatArr[rN][num] != 11 && rN != -1) {
        system("cls");
        printf("Your assigned seat is now at %c%d for %s at %s\n", row, num + 1,
               c->Connect.MovieTitle, c->Timeslot);
        c->seatArr[rN][num] = 11; // seat is now taken
        c->Occupancy++;
        c->currentTix++;
        validSeat = 1;

        int cInd = t->ticketQuantity;
        t->cart[cInd].CinemaNumber = c->Connect.CinemaNumber;
        strcpy(t->cart[cInd].MovieTitle, c->Connect.MovieTitle);
        temp[0] = letterArray[rN];
        if (num == 9) {
          temp[1] = '1';
          temp[2] = '0';
          temp[3] = '\0';
        } else {
          temp[1] = numbers[num];
          temp[2] = '\0';
        }
        strcpy(t->cart[cInd].SeatNum, temp);
        strcpy(t->cart[cInd].Timeslot, c->Timeslot);
        t->ticketQuantity++;

        /// USER PROMPT
        printf("Add more tickets? Y or N\n<");
        scanf(" %c", &YorN);
        if (YorN == 'Y') {
          validSeat = 0;
          exitStatus = 0;
        } else if (YorN == 'N') {
          exitStatus = 1;
        } else {
          printf("Invalid input.\n");
        }

      } else if (c->seatArr[rN][num] == 11) {
        printf("This seat is already taken. Try again. \n");
        validSeat = 0;
      } else { // error handling
        printf("Invalid input. Try again.\n");
      }
    } else { // error handling
      printf("Invalid input. Try again.\n");
    }
    // newLoop++; TRACING PURPOSES ONLY
  }
  showSeating(c);
}

/* PrintCart - Stores customers tickets into a text file 
@param *Cart = Customers inputted choices from seat selection 
@param s[][6] = SeatingData struct
@returns void
Pre-condition: Ideally customer should have purchased at least 1 ticket, otherwise a blank txt file will be produced
*/

void PrintCart(CustomerCart *Cart, SeatingData s[][6]) {
  int i, j, k;
  int size = Cart->ticketQuantity;
  FILE *fp;

  fp = fopen("ticket.txt", "w");
  printf("Number of Tickets in Cart: %d\n",
         Cart->ticketQuantity); // debug purposes

  for (i = 0; i < size; i++) {
    for (j = 0; j < 6; j++) {
      for (k = 0; k < 6; k++) {
        if (strcmp(Cart->cart[i].Timeslot, s[j][k].Timeslot) == 0 &&
            strcmp(Cart->cart[i].MovieTitle, s[j][k].Connect.MovieTitle) == 0) {
          printf("%s Showtime for %s reset!\n", s[j][k].Timeslot,
                 s[j][k].Connect.MovieTitle);
          s[j][k].currentTix = 0;
        }
      }
    }
    fprintf(fp, "TICKET %d\n", i + 1);
    fprintf(fp, "Cinema Number: %d\n", Cart->cart[i].CinemaNumber);
    fprintf(fp, "Movie Title: %s\n", Cart->cart[i].MovieTitle);
    fprintf(fp, "Showtime: %s\n", Cart->cart[i].Timeslot);
    fprintf(fp, "Seat Number: %s\n", Cart->cart[i].SeatNum);
    fprintf(fp, "\n");
  }

  initCustomerCart(Cart);
  fclose(fp);
}

/*takenSeats - Checks if seats are taken
@param taken[] =  Array to store identifiers of taken seats (ex: A1)
@param s = Seating Data struct to access seat array
@returns nSeat
Pre-condition:N/A.
*/
int takenSeats(SeatingData s, String3 taken[]) {
  int i, j;
  int nSeat = 0;
  char letters[5] = {'A', 'B', 'C', 'D', 'E'};
  char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  String3 temp;

  for (i = 0; i < 5; i++) {    // traverse the rows
    for (j = 0; j < 10; j++) { // traverse the columns
      if (s.seatArr[i][j] == 11) {
        temp[0] = letters[i];
        if (j == 9) {
          temp[1] = '1';
          temp[2] = '0';
          temp[3] = '\0';
        } else {
          temp[1] = numbers[j];
          temp[2] = '\0';
        }
        strcpy(taken[nSeat], temp);
        nSeat++;
      }
    }
  }

  return nSeat;
}

/*resetSeats - resets the seats(called when change schedule)
@param taken = Represents array of seat identifier to get cleared
@param size = size of array
@returns void
Pre-condition:N/A.
*/
void resetSeats(String3 taken[], int size) {
  int i, j;
  int length;

  for (i = 0; i < size; i++) {
    length = strlen(taken[i]);
    for (j = 0; j < length; j++) {
      taken[i][j] = '\0';
    }
  }
}

/*SaveAndExit - Program Terminates and all seat reservations for the day are saved on a text file
@param s[][6] = Struct that contains the seatingdata of the customer
@returns void
Pre-condition:N/A.
*/
void SaveAndExit(SeatingData s[][6]) {
  FILE *fp;
  String10 date;
  time_t t = time(NULL);
  struct tm *tm = localtime(&t); // struct tm declared in time.h
  int i, j, k;

  /// INDEXING FOR SEAT ARRANGEMENTS
  String3 seatsTaken[50];
  int seats = 0;

  char showtext[21] = "show-";
  strftime(date, sizeof(date), "%d-%m-%Y",
           tm); // formatted date, month-day-year

  strcat(showtext, date);
  strcat(showtext, ".txt");

  fp = fopen(showtext, "w");

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      if (s[i][j].Occupancy >
          0) { // Displays only the movies with at least 1 seat taken
        fprintf(fp, "Cinema No: %d\n", s[i][j].Connect.CinemaNumber);
        fprintf(fp, "Title: %s\n", s[i][j].Connect.MovieTitle);
        fprintf(fp, "Time: %s\n", s[i][j].Timeslot);
        fprintf(fp, "Taken Seats: \n");
        seats = takenSeats(
            s[i][j], seatsTaken); // sets number of seats taken and initializes
                                  // the seatsTaken string array
        for (k = 0; k < seats; k++) {
          fprintf(fp, "%s ", seatsTaken[k]);
        }
        resetSeats(seatsTaken, seats); // resets seatsTaken string array
        seats = 0;
        fprintf(fp, "\n\n");
      }
    }
  }
}
