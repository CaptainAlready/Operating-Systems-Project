#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>
#define N 7
 
 int a=0;  /* Μετρητής a ο οποίος θα χρησιμοποιηθεί αργότερα*/

 bool choosing[N]; /*Πίνακας choosing, μεγέθους Ν, ο οποίος για κάθε διεργασία Ν, δείχνει αν βρίσκεται                           στην φάση επιλογής εισιτηρίου.*/

 int  number[N]; /*Πίνακας number, μεγέθους Ν στον οποίο αποθηκεύονται το εισιτήριο κάθε
                  διεργασίας αντίστοιχα.*/

 int  SA[N];  /*Το Shared Array μεγέθους Ν*/


 int child_status; /*Δήλωση μεταβλητής για προσωρινη αποθηκευση της κατάστασης του παιδιού,που
                    χρησιμοποιείται απο την waitpid()*/

 int FindMaxTicket(); /* Δήλωση συνάρτησης FindMaxTicket (Bakery Algorithm) που επιστρέφει int */


 void lock(int i);   /* Δήλωση συνάρτησης lock (Bakery Algorithm), η οποία δεν επιστρέφει κάτι*/


 void unlock(int i); /* Δήλωση συνάρτησης unlock(Bakery Algorithm), η οποία δεν επιστρέφει κάτι*/
 
void criticalRegion(int j);  /*Δήλωση συνάρτησης criticalRegion (Bakery Algorithm) η οποία δεν
                              επιστρέφει κατι */


 void printtable(int arr[]);  /* Δήλωση συνάρτησης για την εκτύπωση πίνακα, η οποία  δεν επιστρέφει  κάτι*/



 int main(){      //Συνάρτηση main όπου υπάρχει ο βασικός εκτελέσιμος κώδικας
    pid_t pid[N]; //Δημιουργία πίνακα pid , μεγέθους Ν και τύπου pid_t

    for(int i=1; i<=N; i++) SA[i]=0; //Αρχικοποίηση SA, ώστε κάθε θέση του να ισούται με 0
    
    printf("Table contents prior algorithm: ");/*Εκτύπωση μηνύματος το οποίο ενημερώνει τον χρήστη*/
    printtable(SA);  /*  Εκτύπωση περιεχομένων του πίνακα SA προτού      */
    printf("\n\n"); /*        εφαρμοστεί ο αλγόριθμος bakery.           */
    
    for (int i = 1; i <=N; i++){ //Βρόχος for ο οποίος θα εκτελεστεί Ν φορές
        
        pid[i] = fork();/*Δημιουργία διεργασίας μέσω της συνάρτησης fork() και αντιστοίχιση του id της                                                   διεργασίας στη θέση i του πίνακα pid*/
        if(pid[i]==0){ /*Ελέγχουμε άμα χρησιμοποιείται θυγατρική διεργασία*/
        lock(i);     /*κλήση της συνάρτησης lock(Bakery Algorithm) ώστε να παγώσει η διεργασία i */
        criticalRegion(i); /*Εισαγωγή της διεργασίας i στη κρίσιμη περιοχή της */
        unlock(i);  /*Κλήση της συνάρτησης unlock ώστε να ξεπαγώσει η διεργασία i */
        a++;  /*Αυξάνουμε τον μετρητή a ο οποίος μετράει τις φορές που εκτελείται ο bakery*/
        }
    }
 
     if(a==N){ /*Εφόσον έχει ολοκληρωθεί η διαδικασία δημιουργίας διεργασιών και εκτέλεσης του bakery algorithm*/
     printf("Table contents after algorithm: ");  /*  Εκτύπωση περιεχομένων του πίνακα SA αφού   */
     printtable(SA);                              /*      εφαρμοστεί ο αλγόριθμος bakery.       */
     printf("\n\n");}
    
 
    for (int i = 1; i <=N; i++) //Περιμένουμε να ολοκληρωθεί η εκτέλεση των διεργασιών
     waitpid(pid[i],&child_status, 0);
 
}
 



void lock(int i){ /* Συνάρτηση lock η οποία φροντίζει το πάγωμα μιας διεργασίας και την ανάθεση εισητηρίου σε διεργασία με βάση τον αλγόριθμο του bakery */

    choosing[i]=true; /*Αλλαγή του choosing σε true για την διεργασία pid στη θέση i αφού ξεκινάει να διαλέγει
                       ticket*/
    int maxticket=FindMaxTicket();  /*Εύρεση μεγίστου εισιτηρίου από όλες τις εργασίες*/
    
    number[i]=maxticket+1;  /*Ανάθεση της τιμής του μεγίστου εισιτηρίου + 1 στον πίνακα number,στη θέση του με δείκτη i*/
    choosing[i]=false; /*Αλλαγή του choosing σε false για την διεργασία στη θέση αφού τελείωσε με την
                        επιλογή*/


 
    for(int j=1; j<=N; j++){ /*Αλγόριθμος bakery για την συνάρτηση lock*/
 
    while(choosing[j]){}
    
        while ((number[j] != 0) && ((number[i], i) > (number[j], j))) {}
    }
}
 




void unlock(int i){ /*Δήλωση συνάρτησης unlock η οποία θέτει στην θέση i του πίνακα number
                     την τιμή 0, αφού η αντίστοιχη διεργασία i εξήλθε από το κρίσιμο κομμάτι της*/
    number[i]=0;
}
 




void criticalRegion(int d){/*Το critical section των διεργασιών, το οποίο αποτελείται από την αύξηση του shared array*/
    for(int i=1; i<=N; i++) SA[i]+=d;
}
 
 



int FindMaxTicket()  /*συνάρτηση η οποία βρίσκει και επιστρέφει το μέγιστο εισιτήριο του πίνακα number*/
{
    int maxticket=0;
    for(int i =1; i<=N; i++)
        if(number[i]>maxticket) maxticket=number[i];
    return maxticket;
}
 



void printtable(int arr[]){ /*συνάρτηση η οποία εκτυπώνει τα περιεχόμενα ενός πίνακα arr*/
    for(int i=1; i<=N; i++) printf("%d ",arr[i]);
}

