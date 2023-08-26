#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tchar.h>
#include <windows.h>
#include <commctrl.h>

#include <conio.h>
#include <mmsystem.h>

#include "Verification.h"
#include "Contact.h"
#include "Entree_Sortie.h"

#define Add_Head 211
#define Add_End 212
#define Add_Pos 213
#define Del_Head 221
#define Del_End 222
#define Del_Pos 223
#define Del_Num 224
#define Del_City 225
#define Del_Ind 226
#define Edit_AD 231
#define Edit_Num 232
#define Show_All 31
#define Search_Num 32
#define Search_Name 33
#define Search_Ind 34
#define Search_City 35
#define Stort1 36
#define Stort2 37
#define Save_File 41
#define Recovery_File 42
#define AHH 50
#define AEE 51
#define APP 522
Liste_Tel SortList(Liste_Tel pList) ;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
/*Fonction*/
void Formulaire(HWND,int) ;
void Show(HWND) ;
void DestroyAlll(HWND) ;
int aff=1 ;
static HBITMAP hBmp,hBmp4 ;
int DelContact(HWND,char *,int) ;
Contact GetInfo(HWND) ;
void SearchDel(HWND,int) ;
int PosValide2(HWND) ;
void SearchEdit(HWND,int) ;
void FormulaireEdit(HWND,Contact,int) ;
void ShowContact(HWND,Contact) ;
void Enregistrement_Contact_All(Liste_Tel) ;
void Enregistrement_Contact_Ind(Liste_Tel,char *) ;
void Enregistrement_Contact_City(Liste_Tel,char *) ;
void SearchShow22(HWND,int) ;
void Show(HWND) ;
void showbar(HWND) ;
Liste_Tel Tri2(Liste_Tel) ;
/*Group box*/
HWND GB1,GB2,GB3,GB4,bckg ,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,text1;
/*Boutton*/
HWND BH,BP,BC,BE,Del,Delt,AH,AE,AP,BDP,BDC,BDI,BDN,hedit ;
/*Input text*/
HWND Numtt,Nomtt,Prenomtt,Villett,Code_postaltt,Ruett,Postt,DNtt,Mailtt,Ajoutertt,Indtt ;
/*Label*/
HWND Numt,Nomt,Prenomt,Villet,Code_postalt,Ruet,Post,DNt,Mailt,Adresset,Ajoutert,Titret,Indt ;
/*Menu*/
HMENU Menu ;
void AddMenus(HWND) ;
/*Show contact*/
void Showbar(HWND) ;
HWND liste_contact,uu ;
/*Exit*/
int exitt=1 ;
/*Varialble*/
Liste_Tel l=NULL,lpl=NULL ;
Contact c,lcl ;
FILE *fp,fppp ;
int choix=0,u,created=0 ;
char pp[50],chind[4],chcity[30] ;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("                                                 Repertoire t�l�phonique");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Repertoire t�l�phonique cr�er par Nassim Ben Nsbi et Fadi Chaalab"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    ShowWindow(hwnd,SW_MAXIMIZE);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {

        case WM_PAINT :
          {

            HDC hdc;
            PAINTSTRUCT ps;

            hdc = BeginPaint(hwnd, &ps);

            DrawState(hdc,NULL,NULL,(long)hBmp,0,0,2,1400,800,DST_BITMAP);
            DrawState(hdc,NULL,NULL,(long)hBmp4,0,0,2,1400,800,DST_BITMAP);

            EndPaint(hwnd, &ps);

            return 0;
          }

        case WM_CREATE :
                hBmp=LoadImage(NULL,"Phone.bmp",IMAGE_BITMAP,1400,700,LR_LOADFROMFILE);
            AddMenus(hwnd) ;
            //bckg = CreateWindow(TEXT("Static"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, -30, 0, 2000, 2000,hwnd,NULL,NULL,NULL) ;
            break ;
        case WM_COMMAND :

            switch(wParam)
            {
                case 71 :
                    MessageBox(hwnd, "Repertoire t�l�phonique a �t� cr�er par :\n\n        \t\t\tNassim Ben Nsib et Fadi Chaalab  \n\nProposer par : Mr Kais Ben Salah", "", MB_OK | MB_ICONASTERISK ) ;
                break ;
                /*Open file*/
                case 1998 :
                    system("start Enoncer.pdf") ;
                    break ;
                case 1314 :
                    system("start Main.txt") ;
                    break ;
                case 1315 :
                    system("start Contact.txt") ;
                    break ;
                case 1316 :
                    system("start Verification.txt") ;
                    break ;
                case 1317 :
                    system("start Entree_Sortie.txt") ;
                    break ;
                case 1818 :
                    system("start liste_contact.txt") ;
                    break ;
                /*Create*/
                case 1 :
                    /*   if(exitt==0&&MessageBox(hwnd,"    Voulez vous enregistrer ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                    {
                        Enregistrement_Contact(l) ;
                        DestroyWindow(hwnd) ;
                        break;
                    }
                    else
                        if (exitt&&MessageBox(hwnd,"       Voulez vous quitter ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                        {
                            DestroyWindow(hwnd) ;
                            break ;
                        }*/
                    l=Recuperation_Contact() ;
                    DestroyAlll(hwnd) ;
                    if(l){
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                        break ;
                    }

                    else
                    {
                            l=NULL ;
                            Formulaire(hwnd,3) ;
                            close(fp) ;
                    }

                    l=NULL ;
                    break ;
                /*Files*/
                case Recovery_File :
                    DestroyAlll(hwnd) ;
                    if(l==NULL)
                    {
                        fp=fopen("liste_contact.txt","r");
                        if(fp==NULL)
                        {
                             MessageBox(hwnd,"Le fichier est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                        {
                             l=Recuperation_Contact() ;
                             created= 1;
                             MessageBox(hwnd,"La recup�ration se fait avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
                        }
                    }
                  /*  else
                        if (MessageBox(hwnd, "       Voulez vous ecraser la liste du contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {

                                 l=Recuperation_Contact() ;
                                created= 1;
                                MessageBox(hwnd,"La recup�ration se fait avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
                            }*/

                        break ;
                case Save_File :
                      DestroyAlll(hwnd) ;
                    if(l==NULL)
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    else
                    {
                        Enregistrement_Contact(l) ;
                        MessageBox(hwnd,"L'enregistrement se fait avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
                        exitt=1 ;

                    }
                    break ;
                /*Tri*/
                case Stort1 :
                    DestroyAlll(hwnd) ;
                    if(l==NULL)
                    {
                             MessageBox(hwnd, "Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                    {
                             Tri1(l) ;
                             MessageBox(hwnd,"La liste du contacts a �t� tri�", "", MB_OK | MB_ICONASTERISK ) ;
                             exitt=0 ;
                    }
                    break ;
                 case Stort2 :
                    DestroyAlll(hwnd) ;
                    if(l==NULL)
                    {
                             MessageBox(hwnd, "Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                    {
                            l=  SortList(l) ;
                             MessageBox(hwnd,"La liste du contacts a �t� tri�", "", MB_OK | MB_ICONASTERISK ) ;
                             exitt=0 ;
                    }
                    break ;
               /*ADD*/
                case 155 :
                    DestroyAlll(hwnd) ;
                    if(l)
                        Formulaire(hwnd,0) ;
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Add_Pos :
                    DestroyAlll(hwnd) ;
                    Formulaire(hwnd,3) ;
                    break ;
                case APP :
                    if(TestInfo(hwnd))
                    {
                        c=GetInfo(hwnd) ;
                        if(Recherche_Tel(l,c.Num_Tel)==0&&PosValide(hwnd))
                        {
                            GetWindowText(Postt,pp,7) ;
                            exitt=0;
                            created=1 ;
                            l=Insere_Pos_Tel(l,c,atoi(pp)) ;
                            if (MessageBox(hwnd, "Le contact a �t� ajout� avec succ�s\n\nVoulez vous ajouer un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                Formulaire(hwnd,3) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                        else
                            if(Recherche_Tel(l,c.Num_Tel))
                                MessageBox(hwnd, "Ce num�ro est d�j� existe dans la liste du contacts", "", MB_OK | MB_ICONEXCLAMATION ) ;
                    }
                    break ;
                case 2111 :
                    if(TestInfo(hwnd))
                    {
                        c=GetInfo(hwnd) ;
                        if(Recherche_Tel(l,c.Num_Tel)==0)
                        {
                            l=Insere_Tete_Tel(l,c) ;
                            exitt=0;
                            if (MessageBox(hwnd, "Le contact a �t� ajout� avec succ�s\n\nVous voulez ajouter un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                Formulaire(hwnd,0) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                        else
                            MessageBox(hwnd, "Ce num�ro est d�j� existe dans la liste du contacts", "", MB_OK | MB_ICONEXCLAMATION ) ;
                    }
                    break ;
                case 2113 :
                     if(TestInfo(hwnd))
                    {
                        c=GetInfo(hwnd) ;
                        if(Recherche_Tel(l,c.Num_Tel)==0)
                        {
                            exitt=0;
                            l=Insere_Queue_Tel(l,c) ;
                            if (MessageBox(hwnd, "Le contact a �t� ajout� avec succ�s\n\nVoulez vous ajouer un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                Formulaire(hwnd,0) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                        else
                            MessageBox(hwnd, "Ce num�ro est d�j� existe dans la liste du contacts", "", MB_OK | MB_ICONEXCLAMATION ) ;
                    }
                    break ;
                case 2112 :
                    if(TestInfo(hwnd))
                    {
                        c=GetInfo(hwnd) ;
                        if(Recherche_Tel(l,c.Num_Tel)==0&&PosValide2(hwnd))
                        {
                            GetWindowText(Postt,pp,7) ;
                            exitt=0;
                            l=Insere_Pos_Tel(l,c,atoi(pp)) ;
                            if (MessageBox(hwnd, "Le contact a �t� ajout� avec succ�s\n\nVoulez vous ajouer un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                Formulaire(hwnd,0) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                        else
                            if(Recherche_Tel(l,c.Num_Tel))
                                MessageBox(hwnd, "Ce num�ro est d�j� existe dans la liste du contacts", "", MB_OK | MB_ICONEXCLAMATION ) ;
                    }
                    break ;
                /*Cancel*/
                case 5000 :
                    DestroyAlll(hwnd) ;
                    break ;
                         /*Exit*/
                case 5 :
                    if(exitt==0&&MessageBox(hwnd,"    Voulez vous enregistrer ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                    {
                        Enregistrement_Contact(l) ;
                        DestroyWindow(hwnd) ;
                    }
                    else
                        if (exitt&&MessageBox(hwnd,"       Voulez vous quitter ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                        {
                            DestroyWindow(hwnd) ;
                        }
                    else
                        if(exitt==0)
                            DestroyWindow(hwnd) ;
                    break ;
                 /*Del*/
                case Del_Head :
                    DestroyAlll(hwnd) ;
                    if(l)
                    {
                        DelContact(hwnd,"",1) ;
                        exitt = 0 ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Del_End :
                    DestroyAlll(hwnd) ;
                     if(l)
                    {
                        DelContact(hwnd,"",2) ;
                        exitt = 0 ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Del_Pos :
                    DestroyAlll(hwnd) ;
                     if(l)
                    {
                        SearchDel(hwnd,3) ;
                        exitt = 0 ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 1000 :
                    if(l)
                    {
                        if(PosValide3(hwnd))
                        {
                            GetWindowText(Postt,pp,7) ;
                            exitt=0;
                            Suppression_Pos(l,atoi(pp)) ;
                            if (MessageBox(hwnd, "Le contact a �t� supprim� avec succ�s\n\nVoulez vous supprimer un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                SearchDel(hwnd,3) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Del_Num :
                    DestroyAlll(hwnd) ;
                     if(l)
                    {
                        SearchDel(hwnd,4) ;
                        exitt = 0 ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 1001 :
                    if(l)
                    {
                        GetWindowText(Numtt,pp,10) ;
                        if(strlen(pp))
                        {
                            if(Num_Tel_Valide(pp)&&strlen(pp)==8)
                            {
                                if(Recherche_Tel(l,pp))
                                {
                                    l=Suppression_Tel_Donne(l,pp) ;
                                    exitt=0 ;
                                    if (MessageBox(hwnd, "Le contact a �t� supprim� avec succ�s\n\nVoulez vous supprimer un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                                    {
                                        DestroyAlll(hwnd) ;
                                        SearchDel(hwnd,4) ;
                                    }
                                    else
                                        DestroyAlll(hwnd) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact a ce num�ro", "", MB_OK | MB_ICONERROR ) ;

                            }
                            else
                                MessageBox(hwnd, "Num�ro invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du num�ro est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                 case Del_City :
                    DestroyAlll(hwnd) ;
                     if(l)
                    {
                        SearchDel(hwnd,5) ;
                        exitt = 0 ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                  case 1002 :
                    if(l)
                    {
                        GetWindowText(Villett,pp,20) ;
                        if(strlen(pp))
                        {
                            if(Verif_Nom(pp))
                            {
                                Ameliorer_Nom(pp) ;
                                if(Recherche_Ville(l,pp))
                                {
                                    l=Suppression_Ville_Donnee(l,pp) ;
                                    exitt=0 ;
                                    if (MessageBox(hwnd, "Les contacts ont �t� supprim�s avec succ�s\n\nVoulez vous supprimer des autres contacts ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                                    {
                                        DestroyAlll(hwnd) ;
                                        SearchDel(hwnd,4) ;
                                    }
                                    else
                                        DestroyAlll(hwnd) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact habite dans cette ville", "", MB_OK | MB_ICONERROR ) ;

                            }
                            else
                                MessageBox(hwnd, "Ville invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du ville est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                  case Del_Ind :
                      DestroyAlll(hwnd) ;
                      if(l)
                            SearchDel(hwnd,6) ;
                      else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                      break ;
                  case 1003 :
                    if(l)
                    {
                        GetWindowText(Indtt,pp,20) ;
                        if(strlen(pp))
                        {
                            if(Verif_Num(pp)&&strlen(pp)==2&&pp[0]!='0'&&pp[0]!='1')
                            {
                                if(Recherche_Ind(l,pp))
                                {
                                    l=Suppression_Ind_Donnee(l,pp) ;
                                    exitt=0 ;
                                    if (MessageBox(hwnd, "Les contact ont �t� supprim�s avec succ�s\n\nVoulez vous supprimer des autres contacts ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                                    {
                                        DestroyAlll(hwnd) ;
                                        SearchDel(hwnd,6) ;
                                    }
                                    else
                                        DestroyAlll(hwnd) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun num�ro a cet indicatif", "", MB_OK | MB_ICONERROR ) ;
                            }
                            else
                                MessageBox(hwnd, "Indicatif invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ de l'indicatif est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                /*Edit*/
                case Edit_Num :
                    DestroyAlll(hwnd) ;
                    if(l)
                    {
                        SearchEdit(hwnd,2) ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 9009 :
                     if(l)
                    {
                        GetWindowText(Numtt,pp,10) ;
                        if(strlen(pp))
                        {
                            if(Num_Tel_Valide(pp)&&strlen(pp)==8)
                            {
                                if(Recherche_Tel(l,pp))
                                {
                                    DestroyAlll(hwnd) ;
                                    lpl=l;
                                    while(strcmp(lpl->Info.Num_Tel,pp))
                                        lpl=lpl->Suivant ;
                                    FormulaireEdit(hwnd,lpl->Info,1) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact a ce num�ro", "", MB_OK | MB_ICONERROR ) ;
                            }
                            else
                                MessageBox(hwnd, "Num�ro invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du num�ro est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Edit_AD :
                    DestroyAlll(hwnd) ;
                    if(l)
                        SearchEdit(hwnd,1) ;
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 9010 :
                    if(l)
                    {
                        GetWindowText(Numtt,pp,10) ;
                        if(strlen(pp))
                        {
                            if(Num_Tel_Valide(pp)&&strlen(pp)==8)
                            {
                                if(Recherche_Tel(l,pp))
                                {
                                    DestroyAlll(hwnd) ;
                                    lpl=l;
                                    while(strcmp(lpl->Info.Num_Tel,pp))
                                        lpl=lpl->Suivant ;
                                    FormulaireEdit(hwnd,lpl->Info,2) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact a ce num�ro", "", MB_OK | MB_ICONERROR ) ;
                            }
                            else
                                MessageBox(hwnd, "Num�ro invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du num�ro est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 6600 :
                    c=GetInfo(hwnd) ;
                    if(TestInfo(hwnd))
                    {
                        lpl->Info=c ;
                        if (MessageBox(hwnd, "L'adresse de contact a �t� modifi� avec succ�s\n\nVoulez vous modifier l'adresse d'un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                SearchEdit(hwnd,1) ;
                            }
                        else
                            DestroyAlll(hwnd) ;
                    }
                    break ;
                case 6700 :
                    c=GetInfo(hwnd) ;
                    if(TestInfo(hwnd))
                    {
                        if(Recherche_Tel(l,c.Num_Tel))
                        {
                            MessageBox(hwnd, "Ce num�ro est d�j� existe dans la liste du contacts", "", MB_OK | MB_ICONEXCLAMATION ) ;
                        }
                        else
                        {
                           lpl->Info=c ;
                            if (MessageBox(hwnd, "Le num�ro de contact a �t� modifi� avec succ�s\n\nVoulez vous modifier le num�ro d'un autre contact ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                            {
                                DestroyAlll(hwnd) ;
                                SearchEdit(hwnd,2) ;
                            }
                            else
                                DestroyAlll(hwnd) ;
                        }
                    }
                    break ;
                /*****Affichage*****/
                case Search_Num :
                    if(l)
                    {
                         DestroyAlll(hwnd) ;
                         SearchShow(hwnd,1) ;
                    }
                    else
                        MessageBox(hwnd, "Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Search_Name :
                    if(l)
                    {
                         DestroyAlll(hwnd) ;
                         SearchShow(hwnd,2) ;
                    }
                    else
                        MessageBox(hwnd, "Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                break ;
                case 8889 :
                    if(l)
                        {
                            GetWindowText(Nomtt,pp,20) ;
                            if(strlen(pp))
                        {
                            if(Verif_Nom(pp))
                            {
                                Ameliorer_Nom(pp) ;
                                if(Recherche_Name(l,pp))
                                {
                                   DestroyAlll(hwnd) ;
                                   Enregistrement_Contact_Name(l,pp) ;
                                   Show(hwnd) ;
                                   showbar(hwnd) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact a ce nom", "", MB_OK | MB_ICONERROR ) ;

                            }
                            else
                                MessageBox(hwnd, "Nom invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du nom est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 4444 :
                    DestroyAlll(hwnd) ;
                    SearchShow(hwnd,1) ;
                    break ;
                case 6666 :
                    if(l)
                    {
                        GetWindowText(Numtt,pp,10) ;
                        if(strlen(pp))
                        {
                            if(Num_Tel_Valide(pp)&&strlen(pp)==8)
                            {
                                if(Recherche_Tel(l,pp))
                                {
                                    DestroyAlll(hwnd) ;
                                    lpl=l;
                                    while(strcmp(lpl->Info.Num_Tel,pp))
                                        lpl=lpl->Suivant ;
                                    ShowContact(hwnd,lpl->Info) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact a ce num�ro", "", MB_OK | MB_ICONERROR ) ;
                            }
                            else
                                MessageBox(hwnd, "Num�ro invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du num�ro est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;

                case Show_All :
                    if(l)
                    {
                        DestroyAlll(hwnd) ;
                        Enregistrement_Contact_All(l) ;
                        Show(hwnd) ;
                        showbar(hwnd) ;
                    }
                    else
                        MessageBox(hwnd, "Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 2222 :
                    if(l)
                    {
                        GetWindowText(Indtt,pp,20) ;
                        if(strlen(pp))
                        {
                            if(Verif_Num(pp)&&strlen(pp)==2&&pp[0]!='0'&&pp[0]!='1')
                            {
                                if(Recherche_Ind(l,pp))
                                {
                                    DestroyAlll(hwnd) ;
                                    Enregistrement_Contact_Ind(l,pp) ;
                                    Show(hwnd) ;
                                    showbar(hwnd) ;
                                }
                            else
                                MessageBox(hwnd, "Auccun num�ro a cet indicatif", "", MB_OK | MB_ICONERROR ) ;
                            }
                            else
                                MessageBox(hwnd, "Indicatif invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ de l'indicatif est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case 3333 :
                       if(l)
                        {
                            GetWindowText(Villett,pp,20) ;
                            if(strlen(pp))
                        {
                            if(Verif_Nom(pp))
                            {
                                Ameliorer_Nom(pp) ;
                                if(Recherche_Ville(l,pp))
                                {
                                   DestroyAlll(hwnd) ;
                                   Enregistrement_Contact_City(l,pp) ;
                                   Show(hwnd) ;
                                   showbar(hwnd) ;
                                }
                                else
                                    MessageBox(hwnd, "Auccun contact habite dans cette ville", "", MB_OK | MB_ICONERROR ) ;

                            }
                            else
                                MessageBox(hwnd, "Ville invalide", "", MB_OK | MB_ICONERROR ) ;
                        }
                        else
                            MessageBox(hwnd, "Champ du ville est vide", "", MB_OK | MB_ICONERROR ) ;
                    }
                    else
                        MessageBox(hwnd,"La liste du contacts est d�j� vide", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Search_Ind :
                    if(l)
                    {
                         DestroyAlll(hwnd) ;
                         SearchShow22(hwnd,2) ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
                case Search_City :
                    if(l)
                    {
                         DestroyAlll(hwnd) ;
                        SearchShow22(hwnd,1) ;
                    }
                    else
                        MessageBox(hwnd,"Il faut charger un fichier", "", MB_OK | MB_ICONERROR ) ;
                    break ;
            }
            break ;

        case WM_CLOSE :
                    if(exitt==0&&MessageBox(hwnd,"    Voulez vous enregistrer ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                    {
                        Enregistrement_Contact(l) ;
                        DestroyWindow(hwnd) ;

                        break;
                    }
                    else
                        if (exitt&&MessageBox(hwnd,"       Voulez vous quitter ?", "", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                        {
                            DestroyWindow(hwnd) ;
                          ///  system("start script.bat") ;
                            break ;
                        }
                    else
                        if(exitt==0)
                        {
                            DestroyWindow(hwnd) ;
                           /// system("start script.bat") ;
                        }

                    break ;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
/******Menu******/
void AddMenus(HWND hwnd)
{
    Menu = CreateMenu() ;
    HMENU MSJMenu = CreateMenu() , DelMenu = CreateMenu() , AddMenu = CreateMenu() , EditMenu = CreateMenu() , SearchMenu = CreateMenu() , SaveRecoveryMenu = CreateMenu() ;
    HMENU Pluss = CreateMenu() , Help = CreateMenu() , Music = CreateMenu() , PlayMusic = CreateMenu() ;
    HMENU Enoncer = CreateMenu() , CodeSource = CreateMenu() ;
    /*Update Contact*/
    AppendMenu(MSJMenu,MF_STRING,(HWND) 155,"&Ajouter un t�l�phone") ;
    AppendMenu(MSJMenu,MF_POPUP,(UINT_PTR)DelMenu,"&Supprimer un t�l�phone") ;
    AppendMenu(MSJMenu,MF_POPUP,(UINT_PTR)EditMenu,"&Modifier les donn�es d'un t�l�phone") ;
    /*Add New Contact*/
  /*  AppendMenu(AddMenu,MF_STRING,Add_Head,"&En t�te") ;
    AppendMenu(AddMenu,MF_STRING,Add_End,"&En queue") ;
    AppendMenu(AddMenu,MF_STRING,Add_Pos,"&Dans une postion") ;*/
    /*Del Contact*/
    AppendMenu(DelMenu,MF_STRING,Del_Head,"&En t�te") ;
    AppendMenu(DelMenu,MF_STRING,Del_End,"&En queue") ;
    AppendMenu(DelMenu,MF_STRING,Del_Pos,"&A partir d'une postion") ;
    AppendMenu(DelMenu,MF_STRING,Del_Num,"&D'un t�l�phone") ;
    AppendMenu(DelMenu,MF_STRING,Del_City,"&D'une ville") ;
    AppendMenu(DelMenu,MF_STRING,Del_Ind,"&D'un indicatif") ;
    /*Edit contact*/
    AppendMenu(EditMenu,MF_STRING,Edit_AD,"&Adresse") ;
    AppendMenu(EditMenu,MF_STRING,Edit_Num,"&T�l�phone") ;
    /*Search and Show contact */
    AppendMenu(SearchMenu,MF_STRING,Show_All,"&Tout les contats") ;
    AppendMenu(SearchMenu,MF_STRING,Search_Num,"&Recherche par num�ro") ;
    AppendMenu(SearchMenu,MF_STRING,Search_Ind,"&Recherche par indicatif") ;
    AppendMenu(SearchMenu,MF_STRING,Search_Name,"&Recherche par nom") ;
    AppendMenu(SearchMenu,MF_STRING,Search_City,"&Recherche par ville") ;
    AppendMenu(SearchMenu,MF_STRING,Stort1,"&Tri 1") ;
    AppendMenu(SearchMenu,MF_STRING,Stort2,"&Tri 2") ;
    /*Save and recovery*/
    AppendMenu(SaveRecoveryMenu,MF_STRING,Save_File,"&Enregistrement") ;
    AppendMenu(SaveRecoveryMenu,MF_STRING,Recovery_File,"&R�cuperation") ;
    /*Plus++*/
    AppendMenu(Pluss,MF_POPUP,(UINT_PTR) 1998,"&Enoncer") ;
    AppendMenu(Pluss,MF_POPUP,(UINT_PTR)CodeSource,"&Code source") ;
    AppendMenu(Pluss,MF_STRING,(UINT_PTR) 1818,"&Ouvrir la liste du contact") ;
    /*Code source*/
    AppendMenu(CodeSource,MF_STRING,(UINT_PTR) 1314,"&Main")  ;
    AppendMenu(CodeSource,MF_STRING,(UINT_PTR) 1315,"&Contact")  ;
    AppendMenu(CodeSource,MF_STRING,(UINT_PTR) 1316,"&Verification")  ;
    AppendMenu(CodeSource,MF_STRING,(UINT_PTR) 1317,"&Entree_Sortie")  ;
    /*Aide*/
    AppendMenu(Help,MF_STRING,71,"&A propos") ;
    //AppendMenu(Help,MF_STRING,72,"&Cr�ateur") ;
    /*First Menu*/
    AppendMenu(Menu,MF_STRING,1,"&Cr�ation") ;
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)MSJMenu,"&Mise � jour") ;
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)SearchMenu,"&Recherche, affichage et tri") ;
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)SaveRecoveryMenu,"&Enregisteremet et recuperation") ;;
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)Pluss,"&Plus++") ;
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)Help,"&Aide") ;
    AppendMenu(Menu,MF_STRING,5,"&Quitter") ;

    SetMenu(hwnd,Menu) ;
}
/****Get inforation****/
Contact GetInfo(HWND hwnd)
{
    char ch[30] ;
    Contact c ;

    GetWindowText(Numtt,ch,9) ;
    strcpy(c.Num_Tel,ch) ;

    GetWindowText(Nomtt,ch,20) ;
    Ameliorer_Nom(ch) ;
    strcpy(c.Nom,ch) ;

    GetWindowText(Prenomtt,ch,20) ;
    Ameliorer_Nom(ch) ;
    strcpy(c.Prenom,ch) ;

    GetWindowText(DNtt,ch,20) ;
    Ameliorer_Date(ch) ;
    strcpy(c.DN,ch) ;

    GetWindowText(Villett,ch,20) ;
    Ameliorer_Nom(ch) ;
    strcpy(c.AD.Ville,ch) ;

    GetWindowText(Ruett,ch,20) ;
    Ameliorer_Nom(ch) ;
    strcpy(c.AD.Rue,ch) ;

    GetWindowText(Code_postaltt,ch,20) ;
    strcpy(c.AD.Code_postal,ch) ;

    GetWindowText(Mailtt,ch,30) ;
    strcpy(c.E_Mail,ch) ;
    return c ;
}
/****Test information****/
int TestInfo(HWND hwnd)
{
    Contact c ;
    c=GetInfo(hwnd) ;

    if(strlen(c.Num_Tel)==0)
    {
         MessageBox(hwnd, "Champ du num�ro est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Num_Tel_Valide(c.Num_Tel)==0)
    {
        MessageBox(hwnd, "Num�ro invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    if(strlen(c.Nom)==0)
    {
         MessageBox(hwnd, "Le champ du nom est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Nom(c.Nom)==0)
    {
        MessageBox(hwnd, "Nom invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    if(strlen(c.Prenom)==0)
    {
         MessageBox(hwnd, "Le champ du prenom est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Nom(c.Prenom)==0)
    {
        MessageBox(hwnd, "Pr�nom invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    Ameliorer_Nom(c.DN);
    if(strlen(c.DN)==0)
    {
         MessageBox(hwnd, "Le champ du date de naissance est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
   if(Date_Valide(c.DN)==0)
    {
        Ameliorer_Nom(c.Nom);
        MessageBox(hwnd, "Date de naissance invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

     if(strlen(c.E_Mail)==0)
    {
         MessageBox(hwnd, "Le champ d'E-Mail est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(E_Mail_Valide(c.E_Mail)==0)
    {
        MessageBox(hwnd, "E-Mail invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    if(strlen(c.AD.Ville)==0)
    {
         MessageBox(hwnd, "Le champ de la ville est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Nom(c.AD.Ville)==0)
    {
        MessageBox(hwnd, "Ville invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    if(strlen(c.AD.Rue)==0)
    {
         MessageBox(hwnd, "Le champ de la rue est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Rue_Valide(c.AD.Rue)==0)
    {
        MessageBox(hwnd, "Rue invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    if(strlen(c.AD.Code_postal)==0)
    {
         MessageBox(hwnd, "Le champ du code postal est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Num(c.AD.Code_postal)==0||strlen(c.AD.Code_postal)!=4)
    {
        MessageBox(hwnd, "Code postal invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    return 1 ;
}
/****Formulair****/
void Formulaire(HWND hwnd,int choix)
{
    char ch1[50]="Contact N : ",ch2[8]  ;
    strcat(ch1,itoa(Taille_Liste_Rep(l)+1,ch2,10)) ;
    int ptt=480,pt=120,pp=45 ;

    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 650,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(ch1),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 550,hwnd, NULL, NULL, 0);

    Numtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 520, pt, 70, 25,hwnd,NULL,NULL,NULL) ;
    Numt = CreateWindow(TEXT("Static"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY , 420, pt, 70, 25,hwnd,NULL,NULL,NULL) ;

    Nomtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp, 220, 25,hwnd,NULL,NULL,NULL) ;
    Nomt = CreateWindow(TEXT("Static"),"Nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp, 50, 25,hwnd,NULL,NULL,NULL) ;

    Prenomtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp*2, 220, 25,hwnd,NULL,NULL,NULL) ;
    Prenomt = CreateWindow(TEXT("Static"),"Pr�nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*2, 70, 25,hwnd,NULL,NULL,NULL) ;

    DNtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 750, pt+pp*3, 80, 25,hwnd,NULL,NULL,NULL) ;
    DNt = CreateWindow(TEXT("Static"),"Date de naissance (sous forme JJ/MM/AAAA) : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*3, 300, 25,hwnd,NULL,NULL,NULL) ;

    Mailtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_LOWERCASE, 520, pt+pp*4, 220, 25,hwnd,NULL,NULL,NULL) ;
    Mailt = CreateWindow(TEXT("Static"),"E-Mail : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*4, 70, 25,hwnd,NULL,NULL,NULL) ;

    Adresset = CreateWindow(TEXT("Static"),"****Adresse****",WS_VISIBLE | WS_CHILD | ES_READONLY, 560, pt+pp*5, 100, 25,hwnd,NULL,NULL,NULL) ;

    Villett = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*6, 220, 25,hwnd,NULL,NULL,NULL) ;
    Villet = CreateWindow(TEXT("Static"),"Ville : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*6, 50, 25,hwnd,NULL,NULL,NULL) ;

    Ruett = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*7, 220, 25,hwnd,NULL,NULL,NULL) ;
    Ruet = CreateWindow(TEXT("Static"),"Rue : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*7, 50, 25,hwnd,NULL,NULL,NULL) ;

    Code_postaltt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 540, pt+pp*8, 40, 25,hwnd,NULL,NULL,NULL) ;
    Code_postalt = CreateWindow(TEXT("Static"),"Code postal : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*8, 100, 25,hwnd,NULL,NULL,NULL) ;

    if(choix==0)
    {
         Titret = CreateWindow(TEXT("Static"),"******Ajouter du contacts******",WS_VISIBLE | WS_CHILD | ES_READONLY, 560, 50, 200, 25,hwnd,NULL,NULL,NULL) ;
        GB3 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 520, 500, 120,hwnd, NULL, NULL, 0) ;
        GB4 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,640, 520, 260, 120,hwnd, NULL, NULL, 0);

        Postt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 820, pt+pp*10, 50, 25,hwnd,NULL,NULL,NULL) ;
        BC = CreateWindow(TEXT("Button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER ,420 , pt+pp*9.7 ,150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        Ajoutert = CreateWindow(TEXT("Static"),"Ajouter en : ",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 650, pt+pp*10, 100, 25,hwnd,NULL,NULL,NULL) ;
        AH = CreateWindow(TEXT("Button"),"T�te",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,790 , pt+pp*9.3 ,50, 25,hwnd,(HWND) 2111,NULL,NULL) ;
        AP = CreateWindow(TEXT("Button"),"Pos",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,760 , pt+pp*10 ,50, 25,hwnd,(HWND) 2112,NULL,NULL) ;
        AE = CreateWindow(TEXT("Button"),"Queue",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,790 , pt+pp*10.7,50, 25,hwnd,(HWND) 2113,NULL,NULL) ;
    }
    else
        {
            Titret = CreateWindow(TEXT("Static"),"******Cr�ation de la liste du contacts******",WS_VISIBLE | WS_CHILD | ES_READONLY, 500, 50, 275, 25,hwnd,NULL,NULL,NULL) ;
            BC = CreateWindow(TEXT("Button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER ,410 , pt+pp*10 ,150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
            AP = CreateWindow(TEXT("Button"),"Ajouter",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 740, pt+pp*10, 150, 50,hwnd,(HWND) APP,NULL,NULL) ;
            Postt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 540, pt+pp*9, 40, 25,hwnd,NULL,NULL,NULL) ;
            Post = CreateWindow(TEXT("Static"),"Position : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*9, 70, 25,hwnd,NULL,NULL,NULL) ;
            GB3 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 550, 500, 90,hwnd, NULL, NULL, 0) ;
        }
}
/*****Test pos****/
int PosValide(HWND hwnd)
{
    char ch[7],ch2[30],ch3[7] ;
    int p,t=Taille_Liste_Rep(l) ;
    GetWindowText(Postt,ch,7) ;
     if(strlen(ch)==0)
    {
         MessageBox(hwnd, "Le champ de postion est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Num(ch)==0)
    {
        MessageBox(hwnd, "Position invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    p=atoi(ch) ;
    if(p<1||p>t+1)
    {
        strcpy(ch2,"Donner une postion entre 1 ") ;
        strcat(ch2," et  ") ;
        itoa(t+1,ch3,10) ;
        strcat(ch2,ch3) ;
        MessageBox(hwnd,ch2,"", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    return p ;
}
int PosValide2(HWND hwnd)
{
    char ch[7],ch2[30],ch3[7] ;
    int p,t=Taille_Liste_Rep(l) ;
    GetWindowText(Postt,ch,7) ;
     if(strlen(ch)==0)
    {
         MessageBox(hwnd, "Le champ de postion est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Num(ch)==0)
    {
        MessageBox(hwnd, "Position invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    p=atoi(ch) ;
    if(p<2||p>t)
    {
        strcpy(ch2,"Donner une postion entre 2 ") ;
        strcat(ch2," et  ") ;
        itoa(t,ch3,10) ;
        strcat(ch2,ch3) ;
        MessageBox(hwnd,ch2,"", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    return p ;
}
int PosValide3(HWND hwnd)
{
    char ch[7],ch2[30],ch3[7] ;
    int p,t=Taille_Liste_Rep(l) ;
    GetWindowText(Postt,ch,7) ;
     if(strlen(ch)==0)
    {
         MessageBox(hwnd, "Le champ de postion est vide", "", MB_OK | MB_ICONERROR ) ;
         return 0 ;
    }
    if(Verif_Num(ch)==0)
    {
        MessageBox(hwnd, "Position invalide", "", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    p=atoi(ch) ;
    if(p<2||p>t-1)
    {
        strcpy(ch2,"Donner une postion entre 2 ") ;
        strcat(ch2," et  ") ;
        itoa(t-1,ch3,10) ;
        strcat(ch2,ch3) ;
        MessageBox(hwnd,ch2,"", MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    return p ;
}
/****Supprisssion contact****/
int DelContact(HWND hwnd,char *ch,int choix)
{
    if(choix==1)
    {
        l=Suppression_Tete(l) ;
        MessageBox(hwnd, "Le contact a �t� supprim� avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
    }
    else
        if(choix==2)
        {
            l=Suppression_Queue(l) ;
            MessageBox(hwnd, "Le contact a �t� supprim� avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
        }
    else
        if(choix==3)
        {
            Suppression_Pos(l,atoi(ch)) ;
            MessageBox(hwnd, "Le contact a �t� supprim� avec succ�s", "", MB_OK | MB_ICONASTERISK ) ;
        }
        return 1 ;
}
/****Search for del****/
void SearchDel(HWND hwnd,int choix)
{
    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 250,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 150,hwnd, NULL, NULL, 0);
    if(choix==3)
    {
        Titret = CreateWindow(TEXT("Static"),"******Suppression d'un contact � partir d'une postion******",WS_VISIBLE | WS_CHILD | ES_READONLY,450 , 50, 380, 25,hwnd,NULL,NULL,NULL) ;
        Postt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 50, 25,hwnd,NULL,NULL,NULL) ;
        Post = CreateWindow(TEXT("Edit"),"Position : ",WS_VISIBLE | WS_CHILD | ES_READONLY | ES_NUMBER, 550, 130, 80, 25,hwnd,NULL,NULL,NULL) ;
        BDP = CreateWindow(TEXT("Button"),"Supprimer",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 1000,NULL,NULL) ;
        BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
    }
    if(choix==4)
    {
        Titret = CreateWindow(TEXT("Static"),"******Suppression d'un contact � partir d'un num�ro donn�******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 420, 25,hwnd,NULL,NULL,NULL) ;
        Numtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
        Numt = CreateWindow(TEXT("Edit"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY | ES_NUMBER, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
        BDP = CreateWindow(TEXT("Button"),"Supprimer",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 1001,NULL,NULL) ;
        BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
    }
    else
        if(choix==5)
        {
            Titret = CreateWindow(TEXT("Static"),"******Suppression du contacts d'une ville donn�e******",WS_VISIBLE | WS_CHILD | ES_READONLY, 470, 50, 360, 25,hwnd,NULL,NULL,NULL) ;
            Villett = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 650, 130, 150, 25,hwnd,NULL,NULL,NULL) ;
            Villet = CreateWindow(TEXT("Edit"),"Ville : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Supprimer",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 1002,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
    else
        if(choix==6)
        {
            Titret = CreateWindow(TEXT("Static"),"******Suppression du contacts � partir d'un indicatif donn�******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 417, 25,hwnd,NULL,NULL,NULL) ;
            Indtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 20, 25,hwnd,NULL,NULL,NULL) ;
            Indt = CreateWindow(TEXT("Edit"),"Indicatif : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 80, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Supprimer",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 1003,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
}
/*******Modification*******/
void SearchEdit(HWND hwnd,int choix)
{
    int ptt=480,pt=120,pp=45 ;
    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 250,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 150,hwnd, NULL, NULL, 0);
    if(choix==1)
    {
        Titret = CreateWindow(TEXT("Static"),"******Recherche du contact et modification de leur adresse******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 417, 25,hwnd,NULL,NULL,NULL) ;
        Numtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
        Numt = CreateWindow(TEXT("Static"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
        BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 9009,NULL,NULL) ;
        BDC = CreateWindow(TEXT("Button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
    }
    else
        if(choix==2)
        {
            Titret = CreateWindow(TEXT("Static"),"******Recherche du contact et modification de leur num�ro******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 417, 25,hwnd,NULL,NULL,NULL) ;
            Numtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            Numt = CreateWindow(TEXT("Edit"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 9010,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
}
void FormulaireEdit(HWND hwnd,Contact c,int choix)
{
    int ptt=480,pt=120,pp=45 ;
    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 650,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 550,hwnd, NULL, NULL, 0);
    if(choix==1)
    {
        Titret = CreateWindow(TEXT("Static"),"******Modification d'adresse de ce conact******",WS_VISIBLE | WS_CHILD | ES_READONLY, 490, 50, 305, 25,hwnd,NULL,NULL,NULL) ;
        Numtt = CreateWindow(TEXT("Static"),c.Num_Tel,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_READONLY | ES_NUMBER, 520, pt, 70, 25,hwnd,NULL,NULL,NULL) ;
        Villett = CreateWindow(TEXT("Edit"),c.AD.Ville,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*6, 220, 25,hwnd,NULL,NULL,NULL) ;
        Ruett = CreateWindow(TEXT("Edit"),c.AD.Rue,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*7, 220, 25,hwnd,NULL,NULL,NULL) ;
        Code_postaltt = CreateWindow(TEXT("Edit"),c.AD.Code_postal,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 540, pt+pp*8, 40, 25,hwnd,NULL,NULL,NULL) ;
        BC = CreateWindow(TEXT("Button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER ,410 , pt+pp*10 ,150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        AH = CreateWindow(TEXT("Button"),"Modifier",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 740, pt+pp*10, 150, 50,hwnd,(HWND) 6600,NULL,NULL) ;
        GB3 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 550, 500, 90,hwnd, NULL, NULL, 0) ;
    }
    else
         if(choix==2)
        {
            Titret = CreateWindow(TEXT("Static"),"******Mdification du num�ro de ce conact******",WS_VISIBLE | WS_CHILD | ES_READONLY, 490, 50, 305, 25,hwnd,NULL,NULL,NULL) ;
            Numtt = CreateWindow(TEXT("Edit"),c.Num_Tel,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 520, pt, 70, 25,hwnd,NULL,NULL,NULL) ;
            Villett = CreateWindow(TEXT("Static"),c.AD.Ville,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_READONLY, 500, pt+pp*6, 220, 25,hwnd,NULL,NULL,NULL) ;
            Ruett = CreateWindow(TEXT("Static"),c.AD.Ville,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_READONLY, 500, pt+pp*7, 220, 25,hwnd,NULL,NULL,NULL) ;
            Code_postaltt = CreateWindow(TEXT("Static"),c.AD.Code_postal,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_READONLY , 540, pt+pp*8, 40, 25,hwnd,NULL,NULL,NULL) ;
            BC = CreateWindow(TEXT("Button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER ,410 , pt+pp*10 ,150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
            AH = CreateWindow(TEXT("button"),"Modifier",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 740, pt+pp*10, 150, 50,hwnd,(HWND) 6700,NULL,NULL) ;
            GB3 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 550, 500, 90,hwnd, NULL, NULL, 0) ;
        }

    Numt = CreateWindow(TEXT("Static"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt, 70, 25,hwnd,NULL,NULL,NULL) ;

    Nomtt = CreateWindow(TEXT("Static"),c.Nom,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp, 220, 25,hwnd,NULL,NULL,NULL) ;
    Nomt = CreateWindow(TEXT("Static"),"Nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp, 50, 25,hwnd,NULL,NULL,NULL) ;

    Prenomtt = CreateWindow(TEXT("Static"),c.Prenom,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp*2, 220, 25,hwnd,NULL,NULL,NULL) ;
    Prenomt = CreateWindow(TEXT("Static"),"Pr�nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*2, 70, 25,hwnd,NULL,NULL,NULL) ;

    DNtt = CreateWindow(TEXT("Static"),c.DN,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 750, pt+pp*3, 80, 25,hwnd,NULL,NULL,NULL) ;
    DNt = CreateWindow(TEXT("Static"),"Date de naissance (sous forme JJ/MM/AAAA) : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*3, 300, 25,hwnd,NULL,NULL,NULL) ;

    Mailtt = CreateWindow(TEXT("Static"),c.E_Mail,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp*4, 220, 25,hwnd,NULL,NULL,NULL) ;
    Mailt = CreateWindow(TEXT("Static"),"E-Mail : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*4, 70, 25,hwnd,NULL,NULL,NULL) ;

    Adresset = CreateWindow(TEXT("Static"),"****Adresse****",WS_VISIBLE | WS_CHILD | ES_READONLY, 560, pt+pp*5, 100, 25,hwnd,NULL,NULL,NULL) ;
    Code_postalt = CreateWindow(TEXT("Static"),"Code postal : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*8, 100, 25,hwnd,NULL,NULL,NULL) ;
    Ruet = CreateWindow(TEXT("Static"),"Rue : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*7, 50, 25,hwnd,NULL,NULL,NULL) ;
    Villet = CreateWindow(TEXT("Static"),"Ville : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*6, 50, 25,hwnd,NULL,NULL,NULL) ;
}
/******Affichage*****/
void SearchShow(HWND hwnd,int choix)
{
    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 250,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 150,hwnd, NULL, NULL, 0);
    if(choix==1)
    {
            Titret = CreateWindow(TEXT("Static"),"******Recherche d'un contact et affichage de leur information******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 430, 25,hwnd,NULL,NULL,NULL) ;
            Numtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            Numt = CreateWindow(TEXT("Edit"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY | ES_NUMBER, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 6666,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
    }
    else
        if(choix==2)
        {
            Titret = CreateWindow(TEXT("Static"),"******Recherche d'un contact et affichage de leur information******",WS_VISIBLE | WS_CHILD | ES_READONLY, 450, 50, 430, 25,hwnd,NULL,NULL,NULL) ;
            Nomtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER , 590, 130, 180, 25,hwnd,NULL,NULL,NULL) ;
            Numt = CreateWindow(TEXT("Edit"),"Nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 520, 130, 50, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 8889,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
}
/*******Afficher contact******/
void ShowContact(HWND hwnd,Contact c)
{
    int ptt=480,pt=120,pp=45 ;

    GB3 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 550, 500, 90,hwnd, NULL, NULL, 0) ;
    BC = CreateWindow(TEXT("Button"),"Terminer",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER ,410 , pt+pp*10 ,150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
    AP = CreateWindow(TEXT("button"),"Autre",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 740, pt+pp*10, 150, 50,hwnd,(HWND) 4444,NULL,NULL) ;

    Titret = CreateWindow(TEXT("Static"),"******Affichage les informations d'un contact******",WS_VISIBLE | WS_CHILD | ES_READONLY, 490, 50, 325, 25,hwnd,NULL,NULL,NULL) ;

    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 650,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 550,hwnd, NULL, NULL, 0);

    Numtt = CreateWindow(TEXT("Static"),c.Num_Tel,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 520, pt, 70, 25,hwnd,NULL,NULL,NULL) ;
    Numt = CreateWindow(TEXT("Edit"),"Num�ro : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt, 70, 25,hwnd,NULL,NULL,NULL) ;

    Nomtt = CreateWindow(TEXT("Static"),c.Nom,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp, 220, 25,hwnd,NULL,NULL,NULL) ;
    Nomt = CreateWindow(TEXT("Edit"),"Nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp, 50, 25,hwnd,NULL,NULL,NULL) ;

    Prenomtt = CreateWindow(TEXT("Static"),c.Prenom,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp*2, 220, 25,hwnd,NULL,NULL,NULL) ;
    Prenomt = CreateWindow(TEXT("Edit"),"Pr�nom : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*2, 70, 25,hwnd,NULL,NULL,NULL) ;

    DNtt = CreateWindow(TEXT("Static"),c.DN,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 750, pt+pp*3, 80, 25,hwnd,NULL,NULL,NULL) ;
    DNt = CreateWindow(TEXT("Edit"),"Date de naissance (sous forme JJ/MM/AAAA) : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*3, 300, 25,hwnd,NULL,NULL,NULL) ;

    Mailtt = CreateWindow(TEXT("Static"),c.E_Mail,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 520, pt+pp*4, 220, 25,hwnd,NULL,NULL,NULL) ;
    Mailt = CreateWindow(TEXT("Edit"),"E-Mail : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*4, 70, 25,hwnd,NULL,NULL,NULL) ;

    Adresset = CreateWindow(TEXT("Edit"),"****Adresse****",WS_VISIBLE | WS_CHILD | ES_READONLY, 560, pt+pp*5, 100, 25,hwnd,NULL,NULL,NULL) ;

    Villett = CreateWindow(TEXT("Static"),c.AD.Ville,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*6, 220, 25,hwnd,NULL,NULL,NULL) ;
    Villet = CreateWindow(TEXT("Edit"),"Ville : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*6, 50, 25,hwnd,NULL,NULL,NULL) ;

    Ruett = CreateWindow(TEXT("Static"),c.AD.Rue,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 500, pt+pp*7, 220, 25,hwnd,NULL,NULL,NULL) ;
    Ruet = CreateWindow(TEXT("Edit"),"Rue : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*7, 50, 25,hwnd,NULL,NULL,NULL) ;

    Code_postaltt = CreateWindow(TEXT("Static"),c.AD.Code_postal,WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER , 540, pt+pp*8, 40, 25,hwnd,NULL,NULL,NULL) ;
    Code_postalt = CreateWindow(TEXT("Edit"),"Code postal : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 420, pt+pp*8, 100, 25,hwnd,NULL,NULL,NULL) ;
}
/*******Destroy ALL*******/
void DestroyAlll(HWND hwnd)
{
    DestroyWindow(Nomtt) ;
    DestroyWindow(Nomt) ;

    DestroyWindow(Prenomtt) ;
    DestroyWindow(Prenomt) ;

    DestroyWindow(Numtt) ;
    DestroyWindow(Numt) ;

    DestroyWindow(Villett) ;
    DestroyWindow(Villet) ;

    DestroyWindow(Postt) ;
    DestroyWindow(Post) ;

    DestroyWindow(Mailtt) ;
    DestroyWindow(Mailt) ;

    DestroyWindow(Ruett) ;
    DestroyWindow(Ruet) ;

    DestroyWindow(Code_postaltt) ;
    DestroyWindow(Code_postalt) ;

    DestroyWindow(DNtt) ;
    DestroyWindow(DNt) ;

    DestroyWindow(Indtt) ;
    DestroyWindow(Indt) ;

    DestroyWindow(GB1) ;
    DestroyWindow(GB2) ;

    DestroyWindow(BC) ;
    DestroyWindow(BH) ;
    DestroyWindow(BE) ;
    DestroyWindow(BP) ;
    DestroyWindow(BE) ;

    DestroyWindow(GB1) ;
    DestroyWindow(GB2) ;
    DestroyWindow(GB3) ;
    DestroyWindow(GB4) ;

    DestroyWindow(AHH) ;
    DestroyWindow(Titret) ;
    DestroyWindow(AEE) ;
    DestroyWindow(APP) ;
    DestroyWindow(AP) ;
    DestroyWindow(AH) ;
    DestroyWindow(AE) ;
    DestroyWindow(Adresset) ;
    DestroyWindow(Ajoutert) ;

    DestroyWindow(BDC) ;
    DestroyWindow(BDP) ;

    DestroyWindow(B1) ;
    DestroyWindow(B2) ;
    DestroyWindow(B3) ;
    DestroyWindow(B4) ;
    DestroyWindow(B5) ;
    DestroyWindow(B6) ;
    DestroyWindow(B7) ;
    DestroyWindow(B8) ;
    DestroyWindow(B9) ;
    DestroyWindow(B10) ;

    DestroyWindow(hedit) ;

    DestroyWindow(text1) ;
  // bckg = CreateWindow(TEXT("Static"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, -30, 0, 2000, 2000,hwnd,NULL,NULL,NULL) ;
 hBmp4=LoadImage(NULL,"Phone2.bmp",IMAGE_BITMAP,1400,700,LR_LOADFROMFILE);


}
/******Enregistrement******/
void Enregistrement_Contact_All(Liste_Tel l)
{
    FILE *ff;
    int i=0 ;
    ff=fopen("temp.txt","w");
    fprintf(ff,"\n") ;
    while(l)
    {
         i++ ;
        fprintf(ff," %-4d%c%-3c%-11s%-18s%-18s%-15s%-18s%-18s%-10s%-28s\n",i,l->Info.Num_Tel[0],l->Info.Num_Tel[1],l->Info.Num_Tel,l->Info.Nom,l->Info.Prenom,l->Info.DN,l->Info.AD.Ville,l->Info.AD.Rue,l->Info.AD.Code_postal,l->Info.E_Mail) ;
        fprintf(ff,"----------------------------------------------------------------------------------------------------------------------------------------------\n") ;
        l=l->Suivant;
    }
    fclose(ff);
}
void Enregistrement_Contact_City(Liste_Tel l,char *ch)
{
    FILE *ff;
    int i=0 ;
    ff=fopen("temp.txt","w");
    fprintf(ff,"\n") ;
    while(l)
    {
        if(strcmp(ch,l->Info.AD.Ville)==0)
        {
            i++ ;
           fprintf(ff," %-4d%c%-3c%-11s%-18s%-18s%-15s%-18s%-18s%-10s%-28s\n",i,l->Info.Num_Tel[0],l->Info.Num_Tel[1],l->Info.Num_Tel,l->Info.Nom,l->Info.Prenom,l->Info.DN,l->Info.AD.Ville,l->Info.AD.Rue,l->Info.AD.Code_postal,l->Info.E_Mail) ;
           fprintf(ff,"----------------------------------------------------------------------------------------------------------------------------------------------\n") ;
        }
        l=l->Suivant;

    }
    fclose(ff);
}
void Enregistrement_Contact_Ind(Liste_Tel l,char *ch)
{
    FILE *ff;
    int i=0 ;
    ff=fopen("temp.txt","w");
    fprintf(ff,"\n") ;
    while(l)
    {
        if(strstr(l->Info.Num_Tel,ch)==l->Info.Num_Tel)
        {
            i++ ;
            fprintf(ff," %-4d%c%-3c%-11s%-18s%-18s%-15s%-18s%-18s%-10s%-28s\n",i,l->Info.Num_Tel[0],l->Info.Num_Tel[1],l->Info.Num_Tel,l->Info.Nom,l->Info.Prenom,l->Info.DN,l->Info.AD.Ville,l->Info.AD.Rue,l->Info.AD.Code_postal,l->Info.E_Mail) ;
           fprintf(ff,"----------------------------------------------------------------------------------------------------------------------------------------------\n") ;
        }
        l=l->Suivant;
    }
    fclose(ff);
}
void Enregistrement_Contact_Name(Liste_Tel l,char *ch)
{
    FILE *ff;
    int i=0 ;
    ff=fopen("temp.txt","w");
    fprintf(ff,"\n") ;
    while(l)
    {
        if(strstr(l->Info.Nom,ch))
        {
            i++ ;
            fprintf(ff," %-4d%c%-3c%-11s%-18s%-18s%-15s%-18s%-18s%-10s%-28s\n",i,l->Info.Num_Tel[0],l->Info.Num_Tel[1],l->Info.Num_Tel,l->Info.Nom,l->Info.Prenom,l->Info.DN,l->Info.AD.Ville,l->Info.AD.Rue,l->Info.AD.Code_postal,l->Info.E_Mail) ;
           fprintf(ff,"----------------------------------------------------------------------------------------------------------------------------------------------\n") ;
        }
        l=l->Suivant;
    }
    fclose(ff);
}
void SearchShow22(HWND hwnd,int choix)
{
    GB1 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,300, 30, 700, 250,hwnd, NULL, NULL, 0);
    GB2 = CreateWindow(TEXT("BUTTON"), TEXT(""),WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP ,400, 90, 500, 150,hwnd, NULL, NULL, 0);
    if(choix==1)
    {
            Titret = CreateWindow(TEXT("Static"),"******Recherche du contact par ville******",WS_VISIBLE | WS_CHILD | ES_READONLY, 530, 50, 270, 25,hwnd,NULL,NULL,NULL) ;
            Villett = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 650, 130, 150, 25,hwnd,NULL,NULL,NULL) ;
            Villet = CreateWindow(TEXT("Edit"),"Ville : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 70, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 3333,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
    else
        if(choix==2)
        {
            Titret = CreateWindow(TEXT("Static"),"******Recherche du contact par indicatif******",WS_VISIBLE | WS_CHILD | ES_READONLY, 520, 50, 295, 25,hwnd,NULL,NULL,NULL) ;
            Indtt = CreateWindow(TEXT("Edit"),"",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER | ES_NUMBER, 650, 130, 20, 25,hwnd,NULL,NULL,NULL) ;
            Indt = CreateWindow(TEXT("Edit"),"Indicatif : ",WS_VISIBLE | WS_CHILD | ES_READONLY, 550, 130, 80, 25,hwnd,NULL,NULL,NULL) ;
            BDP = CreateWindow(TEXT("Button"),"Rechercher",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 720, 180,150, 50,hwnd,(HWND) 2222,NULL,NULL) ;
            BDC = CreateWindow(TEXT("button"),"Annuler",WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 420, 180, 150, 50,hwnd,(HWND) 5000,NULL,NULL) ;
        }
}
/****Open files****/
void Show(HWND hwnd)
{
     HFONT hFont;
     char s[20]="temp.txt" ;
     FILE *f ;
    f = fopen(s,"rb") ;
    fseek(f,0,SEEK_END) ;
    int _size = ftell(f) ;
    rewind(f) ;
    char data[_size+1] ;
    fread(data,_size,1,f) ;
    data[_size] = '\0' ;
    SetWindowText(hedit,data) ;
    hedit = CreateWindow("Edit",data,WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | ES_AUTOHSCROLL | WS_VSCROLL | WS_BORDER | WS_HSCROLL | ES_READONLY,70,80,1172,580,hwnd,NULL,NULL,NULL) ;
    hFont = (HFONT)GetStockObject(OEM_FIXED_FONT);
             SendMessage(hedit,WM_SETFONT,(UINT)hFont,TRUE);
             SendMessage(hedit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
                                                              MAKELONG(5, 5));
}
void showbar(HWND hwnd)
{
    int x,pos=70,t[10]={40,32,80,140,140,125,140,140,95,220} ;
    char tn[][20]={"N","Ind","Num�ro","Nom","Prenom","Date de naissance","Ville","Rue","Code postal","E-Mail"} ;
        B1 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B2 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B3 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B4 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B5 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B6 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B7 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B8 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B9 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
        B10 = CreateWindow("Button",tn[x],WS_VISIBLE | WS_CHILD, pos+1, 56, t[x], 23, hwnd,NULL,NULL,NULL) ;
        pos+=t[x] ;
        x++ ;
    text1 = CreateWindow(TEXT("Static"),"  Gestion de repertoire t�l�phonique",WS_VISIBLE | WS_CHILD | SS_CENTER , 550, 20, 250, 23,hwnd,NULL,NULL,NULL) ;
}
Liste_Tel Tri2(Liste_Tel l)
{
    Liste_Tel p=l,p2,r,temp,l1,l2 ;
    l=NULL ;
    while(p->Suivant->Suivant)
    {
        p2=p ;
        r=p ;
        while(p2->Suivant)
        {
            l1=atoi(r->Info.Num_Tel) ;
            l2=atoi(p2->Suivant->Info.Num_Tel) ;
            if(l2<l1)
            {
                r=p2 ;
            }
            p2=p2->Suivant ;
        }
        if(r==p)
        {
            p=p->Suivant ;
            temp=p ;
        }
        else
            temp=r->Suivant ;
        r->Suivant=temp->Suivant ;

        temp->Suivant=l ;
        l=temp ;
        p=p->Suivant ;
    }
   /* p->Suivant=l;
    l=p;*/
    return l ;
}
Liste_Tel MergeLists(Liste_Tel pSrc1, Liste_Tel pSrc2) ;
Liste_Tel SortList(Liste_Tel pList)
{
    int NUMLISTS=Taille_Liste_Rep(pList);
    Liste_Tel aList[NUMLISTS];             /* array of lists */
    Liste_Tel pNode;
    Liste_Tel pNext;
    int i;
    if(pList == NULL)               /* check for empty list */
        return NULL;
    for(i = 0; i < NUMLISTS; i++)   /* zero array */
        aList[i] = NULL;
    pNode = pList;                  /* merge nodes into array */
    while(pNode != NULL){
        pNext = pNode->Suivant;
        pNode->Suivant = NULL;
        for(i = 0; (i < NUMLISTS) && (aList[i] != NULL); i++){
            pNode = MergeLists(aList[i], pNode);
            aList[i] = NULL;
        }
        if(i == NUMLISTS)           /* don't go past end of array */
            i--;
        aList[i] = pNode;
        pNode = pNext;
    }
    pNode = NULL;                   /* merge array into one list */
    for(i = 0; i < NUMLISTS; i++)
        pNode = MergeLists(aList[i], pNode);
    return pNode;
}

/* mergelists -  compare uses src2 < src1           */
/* instead of src1 <= src2 to be similar to C++ STL */

Liste_Tel MergeLists(Liste_Tel pSrc1, Liste_Tel pSrc2)
{
    int rep;
Liste_Tel pDst = NULL;                  /* destination head ptr */
Liste_Tel* ppDst = &pDst;               /* ptr to head or prev->next */
    if(pSrc1 == NULL)
        return pSrc2;
    if(pSrc2 == NULL)
        return pSrc1;
    while(1){
        rep=strncmp(pSrc1->Info.Num_Tel,pSrc2->Info.Num_Tel,2);
                if(rep>0){  /* if src2 < src1 */
            *ppDst = pSrc2;
            pSrc2 = *(ppDst = &(pSrc2->Suivant));
            if(pSrc2 == NULL){
                *ppDst = pSrc1;
                break;
            }
        } else {                        /* src1 <= src2 */
            *ppDst = pSrc1;
            pSrc1 = *(ppDst = &(pSrc1->Suivant));
            if(pSrc1 == NULL){
                *ppDst = pSrc2;
                break;
            }
        }
    }
    return pDst;
}
