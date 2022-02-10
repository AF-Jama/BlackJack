#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define BUST 0
#define IN_PLAY 1
#define NUMOFPLAYERS 5
#define N_SUITS (4) //total number of ranks (Hearts,Spades,Diamond,Cluubs)
#define N_RANKS (13) //Number of ranks from Ace - Jack (Ace  1 2 3 4 5 6 7 8 9  K Q J)
#define N_CARDS (N_SUITS * N_RANKS) //total number of cards in a standard deck (52)
static int index; //index of array adapts
/*This is a blackjack game simulator, that can at most can accomodate five people playing a game*/

// enum bool flag; //declared with variable 'flag'

// const int NUMOFPLAYERS = 5;

struct Player
{
    //Player struct that contains player information that changes state
    char *first_name; //player name - has to be declared by players every time a session/game is started,currently a NULL(0) pointer by defualt
    int total; // total that initilaises to zero
    int state; //player starts off with boolean True meaning they are in the game,want to use enum but cant figure out how to implement it in struct
    //if state is BUST then player is no longer in game
    int blackJack; //signifies if player has rolled a blackjack,set to false intitially
}Game[NUMOFPLAYERS]; //Game array that contains players struct as elements of length 5


struct Dealer
{
    int total; //dealer total 
}Dealer; //Dealer struct -- struct Dealer Dealer

void intialise(){
    //takes in one argument which is the number of players must be a minumum of 2 and maximum of 5
    index = 51;
    char name[50];
    int len;
    for(int i = 0; i<NUMOFPLAYERS; i++){
        //triggers loop which instantiates each player
        printf("\nPlayer %d enter your first name:",i+1);
        gets(name); // gets method reads single line before '\n' and returns pointer that points fist charecter of charecter array
        len  = strlen(name)+1; // len of name including null charecter '\0'
        Game[i].first_name = malloc(len); //assigns required mem and pointer points to first element in memory
        strcpy(Game[i].first_name,name);
        //bool, during initiasation each player is still in play so they are given bool true available from #bool.h, if player becomes BUST then state becomes FALSE
        Game[i].state = true;
        Game[i].blackJack = false;
        Game[i].total = 0;
        // printf("\nTesting");
    }
    Dealer.total = 0;
    //Welcome each player

    printf("\nWelcome to the Game, %s %s %s %s and %s",Game[0].first_name,Game[1].first_name,Game[2].first_name,Game[3].first_name,Game[4].first_name);

}


typedef enum
{
   Diamonds, Clubs, Hearts, Spades

} Suit; //enum with all possible suits

typedef enum
{
   Two, Three, Four, Five, Six, Seven,
   Eight, Nine, Ten, Jack, Queen, King, Ace

} Rank; //enum with all possible ranks

Rank rank; //NOTE: enum object name is equal to zero by defualt 

typedef struct
{
    //struct containing two members each enums of the suit and rank of a card -- structure represents a single card
   Suit mSuit;
   Rank mRank;

} Card; 


static const char *suitToString(Suit suit)
{
   char *theString = "N/A";

   switch(suit)
   {
      case Diamonds: theString = "Diamonds"; break;
      case Clubs   : theString = "Clubs";    break;
      case Hearts  : theString = "Hearts";   break;
      case Spades  : theString = "Spades";   break;
   }

   return(theString);
}


static const char *rankToString(Rank rank)
{
   char *theString = "N/A";

   switch(rank)
   {
      case Two  : theString = "Two";   break;
      case Three: theString = "Three"; break;
      case Four : theString = "Four";  break;
      case Five : theString = "Five";  break;
      case Six  : theString = "Six";   break;
      case Seven: theString = "Seven"; break;
      case Eight: theString = "Eight"; break;
      case Nine : theString = "Nine";  break;
      case Ten  : theString = "Ten";   break;
      case Jack : theString = "Jack";  break;
      case Queen: theString = "Queen"; break;
      case King : theString = "King";  break;
      case Ace  : theString = "Ace";   break;
   }

   return(theString); //returns pointer to string literal back to method
}

static int RanktoInt(const char *string){
   //takes one argument which is a pointer to a charecter -- in this case will be a pointer to theString which is returned from rankToString
   int userChoice;
   if(strcmp(string,"Two") == 0) return 2;
   else if(strcmp(string,"Three") == 0) return 3;
   else if(strcmp(string,"Four") == 0) return 4;
   else if(strcmp(string,"Five") == 0) return 5;
   else if(strcmp(string,"Six") == 0) return 6;
   else if(strcmp(string,"Seven") == 0) return 7;
   else if(strcmp(string,"Eight") == 0) return 8;
   else if(strcmp(string,"Nine") == 0) return 9;
   else if(strcmp(string,"Ten") == 0) return 10;
   else if(strcmp(string,"Jack") == 0) return 10;
   else if(strcmp(string,"Queen") == 0) return 10;
   else if(strcmp(string,"King") == 0) return 10;
   else if(strcmp(string,"Ace") == 0){
      printf("\nDo you want your ace to have a value of 1 or 11");
      scanf("\n%d",&userChoice);
      if(userChoice == 1) return 1;
      else if(userChoice == 11) return 11;
      else return 1; //if user enters a choice that is neither 1 or 11 then they will automatically have thier ace have a value of 1, this is given as value of 1 is less distructive than 11

   };



}

static void showCard(Card *cardPtr)
{
   printf("{ %s of %s }\n", rankToString(cardPtr->mRank), suitToString(cardPtr->mSuit));
}

static void showCards(Card *cards, int nCards)
{
   for(int i = 0; i < nCards; i ++)
      showCard(cards + i);
}

static Card makeCard(Suit suit, Rank rank) //method makes card and takes in two arguments that makes up a card the rank and the suit, this then returns a card of type Card
{
   Card theCard = { 0 }; //card struct members initialised to zero

   theCard.mSuit = suit; //suit of card is set here
   theCard.mRank = rank; //rank of card is set here

   return(theCard); //returns card of type Card
}

static int getRandomValue() //gets random value
{
   static bool first = true; 

   if(first)
   {
      first = false;
      srand((int)time(0)); //seed
   }

   return(rand()); //returns random number
}

static void shuffle(Card *cards, int nCards) //shuffles all 52 cards, takes in two arguments pointer to Card struct and number of cards which is (52), pointer to type Card struct
{
   for(int i = nCards - 1; i > 0; i --) 
   //triggers loop and loops from index 51 and 1
   {
      int index = getRandomValue() % (i + 1); //returs random index between 0 and 51,this will be the random index that a card is placed in the array. ie: mimics shuffling
      //swap elements of array which is an array of type struct Card
      Card tmp     = cards[i]; // creates temporary Card type struct and set to card element in Card type array
      cards[i]     = cards[index]; // Card element struct at position i and swapped with card element at a random index. 
      cards[index] = tmp; // card at random index is swapped with Card at index i
   }
}

static void banner(const char *msg)
{
   printf("============================\n");
   printf("%s\n", msg);
   printf("============================\n\n");
}

static void CheckTotals(struct Player *);

static void CreateDeck(Card *cards){
   //method takes in one method which a pointer to type Card -- in this case it is a Card struct array
   Suit suit = Diamonds;
   int index = 0;
   for(int i = 0; i<N_SUITS; i++){
      //triggers loop that loop through each suit
      Rank rank = Two;
      for(int j = 0; j<N_RANKS; j++){
         //triggers loop that loops through each rank for each suit and creates Card element with a suit and rank
         cards[index++] = makeCard(suit,rank); //creates card and is returned in Card struct array as we iterate through each Card struct array 
         rank++; //increments ranks by 1 on every trigger of the loop
      }
      suit++;
   }
}

static void HandingOut(Card *cards,struct Player *p){
   //takes 3 arguments Card struct pointer, struct Player pointer that points to struct Player array,and struct Dealer pointer 
   //hands out two cards each to each player and two cards to dealer
   for(int i = 0; i<NUMOFPLAYERS; i++){
      //triggers loop and loops through struct type player
      int count = 0;
      printf("\nPlayer %s",p[i].first_name);
      for(int k = index; count <2 && index>=0; k--,index--){
         //triggers loop that adds value of rank to player total, simulating the handing out of cards
         p[i].total += RanktoInt(rankToString(cards[k].mRank)); //need to be able to sum up total based on rank,also has to prompt user on whether they want an ACE to be counted as a 1 or 11
         ++count; //increments the number of cards given
      }
      if(p[i].total>21) p[i].state = false;
      else if(p[i].total == 21) p[i].blackJack == true;
      else continue;
      
   }
   printf("\nTotals so far");
   CheckTotals(p);
   //simulates giving cards to dealer after two cards given each to players
   // int firstcard; //value of first card handed to dealer which will be shown to players
   // for(int i = 0; i<2; i++){
   //    //triggers loop that simulates dealer giving cards to themself from the stack
   //    d->total+= RanktoInt(rankToString(cards[index].mRank));
   // }
}

static void CheckTotals(struct Player *pntr){
   //method takes in one argument which is a pntr to type struct Player -- in this case it will be array Game which is of type struct Player
   //checks the total score for each player
   printf("\n=============================================");
   printf("\nChecking total");
   for(int i = 0; i<NUMOFPLAYERS; i++){
      //triggers loop to check total for each playeR
      if (pntr[i].state == 1 && pntr[i].blackJack == 1)
      {
         printf("\nPlayer %s is still has hand total to blackjack",pntr[i].first_name);
      }

      else if(pntr[i].state == 1 && pntr[i].blackJack == 0){
         printf("\nPlayer %s still in game with hand total %d",pntr[i].first_name,pntr[i].total);
      }
      else{
         printf("\nPlayer %s you have busted",pntr[i].first_name);
      }
      

   }
}

static void getFirstDealerCard(struct Dealer *d,Card *cards){
   //method takes two argument which is a pointer to type struct Dealer and pointer to type Card
   d->total+= RanktoInt(rankToString(cards[index].mRank));
   --index;
   printf("\nDealer first card is %d",d->total); //tells player the dealers first card
   d->total+= RanktoInt(rankToString(cards[index].mRank)); //gets second card for dealer but does not show the total value with the card
   --index;
}

//logic behind allowing players the option to hit(take a card) or stand(not take a card)
static void AskPlayers(struct Player *ppntr,Card *cards){
   //method takes on argument which is a pointer to type struct Player -- in this case is struct Player array -- Game and pointer to type Card -- struct Card which is an array of cards that form a deck
   //method asks each player if they want to stand or hit,skips if they have a hand greater than 21 as their state would be false
   char c; 
   for(int i = 0; i<NUMOFPLAYERS; i++){
      int running = true;
      if(ppntr[i].state == 1  && ppntr[i].blackJack != true){
         //triggers if player has not bust from recieving its two cards
         printf("\nPlayer %d",i+1);
         //triggered if player has a hand lower than or equal to 21 which means they are still in the game
         for(;;){
            printf("\nPlayer %s do you want to hit or stand your current hand of %d:",ppntr[i].first_name,ppntr[i].total);
            c = getch();
            if(c == 'h'){
               ppntr[i].total += RanktoInt(rankToString(cards[index].mRank));
               printf("\nPlayer %s your total hand is now %d",ppntr[i].first_name,ppntr[i].total);
               index --;
               if(ppntr[i].total == 21){
                  //triggered if player total is 21
                  ppntr[i].blackJack = true;
                  break;
               }
               else if(ppntr[i].total>21){
                  printf("Player %s you have busted",ppntr[i].first_name);
                  ppntr[i].state = false;
                  break;
               }
               continue;
            }

            else if (c == 's')
            {
               //hold triggers the infinite for loop to end and the dealer to move through to the next player hand
               if(ppntr[i].total == 21){
                  //triggered if player total equals to 21, player member(blackJack) becomes true
                  ppntr[i].blackJack == true;
               }
               break;
            }

            else continue;
            
         }
      }
   }

   CheckTotals(ppntr); //checks totals for second time after players have hit or stood and if player total is >21 then state member is set to false
   
}


static void DealerTotal(struct Dealer *dntr,Card *cards){
   //method takes in two argument which is a pntr to type struct Dealer -- in this case it will be array Game which is of type struct Player and pointer to type Card that points to deck of cards array
   //checks the total score of dealer
   printf("\nDealer total after two card is %d",dntr->total);
   while (dntr->total<17)
   {
      //loop triggers and runs until condition evalulates to false
      dntr->total +=RanktoInt(rankToString(cards[index].mRank));
      --index;
   }
   printf("\nDealer final total is %d",dntr->total);
   
}


static void findWinners(struct Player *p,struct Dealer *d){
   //method takes two arguments,pointer to type struct Player and pointer to type struct Dealer
   //method finds winners of round
   if(d->total >21){
      //dealer busts and valid player with state == 1 have won
      for(int i = 0; i<NUMOFPLAYERS; i++){
         if(p[i].state == 1) printf("\nPlayer %s has beaten the dealer and has won",p[i].first_name);
      }

   }

   else if (d->total == 21)
   {
      printf("Dealer has hand totalling black jack and has won");
      int count = 0;
      for(int i =0; i<NUMOFPLAYERS; i++){
         //loops to search for players that also have a hand that totals to a blackjack
         if(p[i].blackJack == 1){
            printf("\nPlayer %s has also drawn a blackjack",p[i].first_name);
            ++count;
         }
      }
      if(count == 0) printf("No other players have hand totalling to blackjack,hence, Dealer has won");
      else printf("\nDealer and player(s) have hands totalling blackjack");

   }
   
   else if (d->total<21)
   {
      for(int i = 0; i<NUMOFPLAYERS; i++){
         if(p[i].state == 1 && p[i].total>d->total) printf("\nPlayer %s has beaten the dealer and has won",p[i].first_name);
            //triggered if player is still in game and total is greater than dealer total
         
         else if(p[i].state == 1 && p[i].total<d->total) printf("\nPlayer %s you have lost as you card is less than the dealer total hand",p[i].first_name);
         
      }
   }
   
}

int main(){
   // char *stringpntr = "Two";
   char a;
   int play = true;
   while (play)
   {    
      intialise(); //intialises for a session of blackjack with 5 players 
      Card cards[N_CARDS]; //Creates an array of structs 
      CreateDeck(cards); //method creates card deck of cards with each individual card struct element in an array having an suit and rank
      shuffle(cards,N_CARDS); //method shuffle card by assiging each array from index 0 to 51 a random index and swapping the cards at this index
      printf("\nTesting");
      //Handing out cards to each player and dealer,takes two arguments, pointer to Card type(Deck of type struct Card) and pointer to struct Player which is an array of player struct called Game ans struct Dealer pointer to Dealer struct (&Dealer)
      HandingOut(cards,Game); 
      getFirstDealerCard(&Dealer,cards);
      AskPlayers(Game,cards);
      DealerTotal(&Dealer,cards);
      findWinners(Game,&Dealer);
      printf("\nDo you want you want to play again?:");
      a = getch();
      if (a == 'y') continue;
      else play = false;
   }
    return(0);
}