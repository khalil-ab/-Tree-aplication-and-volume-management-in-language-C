#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct elem_arbre
{
    char nom[20];
    char type;//V : Volume F : File R : Repertory
    struct elem_arbre *fils;
    struct elem_arbre *frere;
}
elem_arbre;

typedef struct liste_rep
{
    elem_arbre *rep;
    int pos;
    struct liste_rep *suiv;
    struct liste_rep *prec;
}
liste_rep;

typedef struct liste_volume
{
    elem_arbre *vol;
    struct liste_volume *suiv;
}
liste_volume;

typedef struct chemin
{
    char contenu[30];
    struct chemin *suiv;
}
chemin;

typedef struct pile
{
    elem_arbre *elm;
    struct pile *bas;
} pile;

elem_arbre* initialiser(elem_arbre*rac)
{
    rac=(elem_arbre*)malloc(sizeof(elem_arbre));
    strcpy(rac->nom,"pc");
    rac->fils=NULL;
    rac->frere=NULL;
    rac->type='d';
    return rac;
}

int EstVide(pile *p)
{
    if(p->bas==NULL)
        return 1;
    else
        return 0;
}

pile* Empiler(pile*p,elem_arbre *elem)
{

    pile *s=(pile*)malloc(sizeof(pile));
    s->elm=elem;
    s->bas=p;
    return s;

}

typedef struct pileval
{
    int val;
    struct pileval *bas;
} pileval;

int EstVideval(pileval *p)
{
    if(p->bas==NULL)
        return 1;
    else
        return 0;
}

pileval* Empilerval(pileval*p,int val)
{
    pileval *s=(pileval*)malloc(sizeof(pileval));
    s->val=val;
    s->bas=p;
    return s;
}

int redandonce_nom(elem_arbre *rac,elem_arbre *noeud3,char *nom)
{
    pile *k;
    int stop=0;
    elem_arbre *noeud=rac;
    elem_arbre *p;
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;


    do
    {
        if(noeud->fils!=NULL&&noeud->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud);
        }

        if(noeud->fils!=NULL)
        {

            for(p=noeud->fils; p!=NULL&&p!=noeud3;)
            {
                p=p->frere;
            }

            if(p==noeud3)
            {
                p=noeud->fils;

                while(p->frere!=NULL&&strcmp(p->nom,nom)!=0)
                {
                    p=p->frere;
                }

                if(p->frere==NULL&&strcmp(p->nom,nom)!=0)
                    return 0;
                else
                    return 1;
            }

            noeud=noeud->fils;
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {

                if(EstVide(ppp)!=1)
                {
                    noeud=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

            }
        }
    }
    while(stop!=1);



    return 0;

}

void afficher_itter(elem_arbre rac,liste_rep *lrep)
{
    pile *k;
    int stop=0;
    int i;
    liste_rep *q,*kkkk;
    elem_arbre *noeud=&rac;
    liste_rep *jjjj;
    liste_rep *ptr1,*ptr2,*ptr3;
    int cpt=0;
    pileval*pv=NULL;
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");

    do
    {

        if(lrep==NULL)
        {
            lrep=(liste_rep*)malloc(sizeof(liste_rep));
            lrep->rep=noeud;
            lrep->prec=NULL;
            lrep->suiv=NULL;
            lrep->pos=cpt;
            kkkk=lrep;
        }
        else
        {
            q =(liste_rep*)malloc(sizeof(liste_rep));
            q->rep=noeud;
            q->prec=kkkk;
            q->suiv=NULL;
            kkkk->suiv=q;
            kkkk=kkkk->suiv;
            kkkk->pos=cpt;
        }

        if(noeud->fils!=NULL&&noeud->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud);
        }


        if(noeud->fils!=NULL)
        {
            noeud=noeud->fils;
            pv=Empilerval(pv,cpt);
            cpt=cpt+1;
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {

                if(EstVide(ppp)!=1)
                {

                    jjjj=lrep;
                    while(jjjj!=NULL&&ppp!=NULL&&jjjj->rep!=ppp->elm)
                    {
                        jjjj=jjjj->suiv;
                    }

                    if(jjjj!=NULL)
                        cpt=jjjj->pos;

                    noeud=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

            }
        }
    }
    while(stop!=1);


    ptr1=lrep;

    do
    {
        printf("\n");
        for(i=0; i<ptr1->pos; i++)
        {
            ptr2=lrep;
            ptr3=lrep;

            while(ptr2!=NULL&&ptr2!=ptr1)
            {
                if(ptr2->pos==i)
                {
                    ptr3=ptr2;
                }
                ptr2=ptr2->suiv;
            }


            if(ptr3->rep->frere!=NULL)
                putchar(179);
            else
                printf(" ");

            printf("  ");
        }

        if(ptr1->rep->frere!=NULL)
            putchar(195);
        else
            putchar(192);
        putchar(196);
        printf("%s",ptr1->rep->nom);
        ptr1=ptr1->suiv;
    }
    while(ptr1!=NULL);
}

void creer_fils_frere(elem_arbre *noeud,elem_arbre *rac)
{
    int rep,choix,repeter;
    char nom[20];

    if(noeud->type=='f')
    {
        noeud->fils=NULL;
        printf("\nIs there anything else next to the file %s ? O/N : ",noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->frere=NULL;
        }
        else
        {
            printf("\nWhat is its type ? ");
            printf("\nF- File ");
            printf("\nR- Reportory ");
            printf("\nyour choice : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->frere->fils=NULL;
            noeud->frere->frere=NULL;
            if(choix==70||choix==102)//file
            {
                do
                {
                    printf("\nDonnez le nom du fichier : ");
                    gets(nom);
                    repeter=redandonce_nom(rac,noeud,nom);
                    if(repeter==1)
                        printf("It is better to change your name please !!");
                }
                while(strcmp(nom,"\0")==0||repeter==1);

                strcpy(noeud->frere->nom,nom);
                noeud->frere->type='f';
            }
            else//repertoire
            {
                printf("\nGive the name of the reportory : ");

                do
                {
                    gets(noeud->frere->nom);
                }
                while(strcmp(noeud->frere->nom,"\0")==0);

                noeud->frere->type='r';
            }
            creer_fils_frere(noeud->frere,rac);
        }
    }
    else
    {
        printf("\nis there any content in the reportory %s ? O/N : ",noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->fils=NULL;
        }
        else
        {
            printf("\nWhat is its type ? ");
            printf("\nF- File ");
            printf("\nR- Reportory ");
            printf("\nyour choice : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->fils->fils=NULL;
            noeud->fils->frere=NULL;
            if(choix==70||choix==102)//file
            {
                printf("\nGive the name of the file : ");

                do
                {
                    gets(noeud->fils->nom);
                }
                while(strcmp(noeud->fils->nom,"\0")==0);
                noeud->fils->type='f';
            }
            else//reportory
            {
                printf("\nGive the name of the reportory : ");

                do
                {

                    gets(noeud->fils->nom);

                }
                while(strcmp(noeud->fils->nom,"\0")==0);

                noeud->fils->type='r';
            }
            creer_fils_frere(noeud->fils,rac);
        }

        printf("\nY a t il autre chose a cote du repertoire %s ? O/N : ",noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->frere=NULL;
        }
        else
        {
            printf("\nWhat is its type ? ");
            printf("\nF- File ");
            printf("\nR- Reportory ");
            printf("\nyour choice : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->frere->fils=NULL;
            noeud->frere->fils=NULL;

            if(choix==70||choix==102)//file
            {
                do
                {
                    printf("\nGive the name of the file : ");
                    gets(nom);
                    repeter=redandonce_nom(rac,noeud,nom);
                    if(repeter==1)
                        printf("It is better to change your name please !!");
                }
                while(strcmp(nom,"\0")==0||repeter==1);
                strcpy(noeud->frere->nom,nom);
                noeud->frere->type='f';
            }
            else//repertoire
            {
                printf("\nGive the name of the reportory : ");

                do
                {

                    gets(noeud->frere->nom);

                }
                while(strcmp(noeud->frere->nom,"\0")==0);
                noeud->frere->type='r';
            }
            creer_fils_frere(noeud->frere,rac);
        }
    }
}

int nbr_elem(elem_arbre *elm,char *nom)
{
    if(elm==NULL)
    {
        return 0;
    }
    else
    {
        if(strcmp(elm->nom,nom)==0)
            return 1 + nbr_elem(elm->fils,nom)+nbr_elem(elm->frere,nom);
        else
            return nbr_elem(elm->fils,nom)+nbr_elem(elm->frere,nom);
    }
}

elem_arbre* chercher_elem(char *chem,elem_arbre *rac)
{
    chemin *first=NULL,*last,*elem;
    char *part;
    char seps[]= "\\";
    elem_arbre *noeud=rac;
    int stop=0,trouve;

    part = strtok(chem,seps);

    while(part!=NULL)
    {
        elem=(chemin*)malloc(sizeof(chemin));
        strcpy(elem->contenu,part);
        elem->suiv=NULL;

        if(first==NULL)
        {
            first=elem;
            last=elem;
        }
        else
        {
            last->suiv=elem;
            last=elem;
        }

        part = strtok(NULL,seps);
    }

    do
    {
        if(strcmp(noeud->nom,first->contenu)==0)
        {
            first=first->suiv;
            if(first!=NULL)
            {
                noeud=noeud->fils;
            }
            else
            {
                trouve=1;
                stop=1;
            }
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {
                stop=1;
                trouve=0;

            }
        }

    }
    while(stop!=1);

    if(trouve==0)
        return NULL;
    else
        return noeud;

}

elem_arbre* chercher_pere_d1_elem(char *chem,elem_arbre *rac)
{
    chemin *first=NULL,*last,*elem;
    char *part;
    char seps[]= "\\";
    elem_arbre *noeud=rac;
    elem_arbre *prec;
    int stop=0,trouve;

    part = strtok(chem,seps);


    while(part!=NULL)
    {
        elem=(chemin*)malloc(sizeof(chemin));
        strcpy(elem->contenu,part);
        elem->suiv=NULL;

        if(first==NULL)
        {
            first=elem;
            last=elem;
        }
        else
        {
            last->suiv=elem;
            last=elem;
        }

        part = strtok(NULL,seps);
    }

    do
    {
        if(strcmp(noeud->nom,first->contenu)==0)
        {
            first=first->suiv;
            if(first!=NULL)
            {
                prec=noeud;
                noeud=noeud->fils;
            }
            else
            {
                trouve=1;
                stop=1;
            }
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                prec=noeud;
                noeud=noeud->frere;
            }
            else
            {
                stop=1;
                trouve=0;

            }
        }

    }
    while(stop!=1);

    if(trouve==0)
        return NULL;
    else
        return prec;

}

void ajouter_nv_elem(elem_arbre *rac)
{
    char chem[200],nom[10];
    int choix,rep,repeter;
    elem_arbre *noeud,*nvelem;
    liste_rep *lrep=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nGive the path of a repertory or Volume in which you want to put the new content: \n");
    gets(chem);

    noeud=chercher_elem(chem,rac);


    if(noeud!=NULL)
    {
        if(noeud->type=='f')
        {
            printf("\nThis is the path to a file and not Directory or Volume !!");
            getch();
        }
        else
        {
            if(noeud->type=='d')
            {
                printf("\nThis is the path to your disk and not repertory or Volume !!");
                getch();
            }
            else
            {
                printf("\nWhat is the type of new content ? ");
                printf("\nF- File ");
                printf("\nR- Repertory ");
                printf("\nYour choice : ");

                do
                {
                    choix=getch();
                }
                while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

                nvelem=(elem_arbre*)malloc(sizeof(elem_arbre));
                if(choix==70||choix==102)//file
                {
                    do
                    {
                        printf("\nDGive the name of the file : ");
                        gets(nom);
                        repeter=redandonce_nom(rac,noeud->fils,nom);
                        if(repeter==1)
                            printf("It is better to change your name please !!");
                    }
                    while(strcmp(nom,"\0")==0||repeter==1);
                    strcpy(nvelem->nom,nom);
                    nvelem->type='f';
                }
                else//repertoire
                {
                    do
                    {
                        printf("\nGive the name of the reportory : ");
                        gets(nom);
                        repeter=redandonce_nom(rac,noeud->fils,nom);
                        if(repeter==1)
                            printf("It is better to change your name please !!");
                    }
                    while(strcmp(nom,"\0")==0||repeter==1);
                    strcpy(nvelem->nom,nom);

                    nvelem->type='r';
                }
                nvelem->fils=NULL;
                nvelem->frere=NULL;

                if(noeud->fils==NULL)
                {
                    noeud->fils=nvelem;
                }
                else
                {
                    noeud=noeud->fils;

                    while(noeud->frere!=NULL)
                    {
                        noeud=noeud->frere;
                    }

                    noeud->frere=nvelem;
                }
                printf("New item successfully added !!");

                printf("\n");
                afficher_itter(*rac,lrep);
                printf("\n");

                do
                {
                    noeud=nvelem;
                    printf("\nIs there anything else to add in this path ? O/N : ");
                    do
                    {
                        rep=getch();
                    }
                    while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

                    if(rep==79||rep==111)
                    {
                        printf("\nWhat is the type of new content ? ");
                        printf("\nF- File ");
                        printf("\nR- Reportory ");
                        printf("\nyour choice : ");

                        do
                        {
                            choix=getch();
                        }
                        while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

                        nvelem=(elem_arbre*)malloc(sizeof(elem_arbre));
                        if(choix==70||choix==102)//file
                        {
                            printf("\nGive the name of the file : ");

                            do
                            {
                                gets(nvelem->nom);
                            }
                            while(strcmp(nvelem->nom,"\0")==0);
                            nvelem->type='f';
                        }
                        else//repertoire
                        {
                            printf("\nGive the name of the reportory : ");

                            do
                            {
                                gets(nvelem->nom);
                            }
                            while(strcmp(nvelem->nom,"\0")==0);
                            nvelem->type='r';
                        }
                        nvelem->fils=NULL;
                        nvelem->frere=NULL;
                        noeud->frere=nvelem;
                        printf("New item successfully added !!");


                        printf("\n");
                        afficher_itter(*rac,lrep);
                        printf("\n");
                    }
                }
                while(rep!=78&&rep!=110);
            }
        }
    }
    else
    {
        printf("\nWrong path !!");
        getch();
    }


}

void suppression(elem_arbre *elem)
{
    if(elem->fils!=NULL)
        suppression(elem->fils);
    if(elem->frere!=NULL)
        suppression(elem->frere);

    free(elem);
}

void supprimer_elem(elem_arbre *rac)
{
    char chem[200],chem2[200];
    int rep;
    elem_arbre *noeud,*prec;
    liste_rep *lrep=NULL;

    if(rac==NULL)
    {
        printf("There is nothing to delete !!");
    }
    else
    {
        printf("\n");
        afficher_itter(*rac,lrep);
        printf("\n");

        printf("\nGive the path of the element you want to delete : \n");
        gets(chem);

        strcpy(chem2,chem);

        noeud=chercher_elem(chem,rac);

        if(noeud!=rac)
            prec=chercher_pere_d1_elem(chem2,rac);

        if(noeud==NULL)
        {
            printf("Wrong path !!");
            getch();
        }
        else
        {

            if(noeud->type=='f')
                printf("\nAre you sure you want to delete this file? O/N : ");
            else
            {
                if(noeud->type=='v')
                    printf("\nAre you sure you want to delete this volume? O/N : ");
                else
                {
                    if(noeud->type=='r')
                        printf("\nAre you sure you want to delete this repertory? O/N : ");
                    else
                        printf("\nAre you sure you want to format this disk? ? O/N : ");
                }
            }

            do
            {
                rep=getch();
            }
            while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

            if(rep==78||rep==110)
            {
                printf("\nNo operation has been performed");
                getch();
            }
            else
            {

                if(noeud==rac)
                {
                    suppression(rac->fils);
                    rac->fils=NULL;
                }
                else
                {
                    if(noeud==prec->fils)
                        prec->fils=noeud->frere;
                    else
                        prec->frere=noeud->frere;

                    if(noeud->fils!=NULL)
                        suppression(noeud->fils);
                    free(noeud);
                }
                printf("\nSuccessful deletion !!");

                if(rac->fils!=NULL)
                {
                    printf("\n");
                    afficher_itter(*rac,lrep);
                    printf("\n");
                    printf("\nPress any key to continue");
                }
                getch();
            }
        }
    }
}

void supprimer_elem_couper(elem_arbre *rac,char *chem3)
{
    char chem2[200];
    elem_arbre *noeud,*prec;

    strcpy(chem2,chem3);

    noeud=chercher_elem(chem3,rac);
    prec=chercher_pere_d1_elem(chem2,rac);

    if(noeud==rac)
    {
        suppression(rac);
        rac=NULL;
    }
    else
    {
        if(noeud==prec->fils)
            prec->fils=noeud->frere;
        else
            prec->frere=noeud->frere;

        if(noeud->fils!=NULL)
            suppression(noeud->fils);
        free(noeud);
    }
}

void annuler_un_enreg(elem_arbre *noeud)
{

    if(noeud->fils!=NULL)
        suppression(noeud->fils);
    free(noeud);

}

void ajouter_vol(elem_arbre *rac)
{
    int choix,repeter,rep;
    elem_arbre *elem,*p,*k;
    char nom[20];

    if(rac->fils==NULL)
    {
        elem=(elem_arbre*)malloc(sizeof(elem_arbre));
        rac->fils=elem;
        printf("\nGive the name of your new volume : ");
        do
        {
            gets(elem->nom);
        }
        while(strcmp(elem->nom,"\0")==0);
        k=rac;
    }
    else
    {
        for(p=rac->fils; p->frere!=NULL; p=p->frere);

        do
        {
            printf("\nGive the name of your new volume  : ");
            gets(nom);
            repeter=redandonce_nom(rac,p,nom);
            if(repeter==1)
                printf("It is better to change your name please !!");
        }
        while(strcmp(nom,"\0")==0||repeter==1);

        elem=(elem_arbre*)malloc(sizeof(elem_arbre));
        strcpy(elem->nom,nom);
        p->frere=elem;
        k=p;
    }

    elem->frere=NULL;
    elem->type='v';
    printf("\nWhat is the content of your volume  ? ");
    printf("\nF- File ");
    printf("\nR- Reportory ");
    printf("\nV- Empty ");
    printf("\nYour choice : ");

    do
    {
        choix=getch();
    }
    while(choix!=70&&choix!=102&&choix!=82&&choix!=114&&choix!=86&&choix!=118);// 70F 102f 82R 114r 86V 118v

    if(choix==86||choix==118)//Empty
    {
        elem->fils=NULL;
    }
    else
    {
        elem->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
        if(choix==70||choix==102)//file
        {
            printf("\nGive the name of the file : ");

            do
            {
                gets(elem->fils->nom);
            }
            while(strcmp(elem->fils->nom,"\0")==0);
            elem->fils->type='f';
        }
        else//repertoire
        {
            printf("\nGive the name of the repertory : ");
            do
            {

                gets(elem->fils->nom);

            }
            while(strcmp(elem->nom,"\0")==0);
            elem->fils->type='r';
        }
        creer_fils_frere(elem->fils,rac);
    }


    printf("\nAre you sure you want to save this volume ? O/N : ");
    do
    {
        rep=getch();
    }
    while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

    if(rep==110||rep==78)
    {
        if(k==rac)
        {
            annuler_un_enreg(k->fils);
            rac->fils=NULL;
        }
        else
        {
            annuler_un_enreg(k->frere);
            k->frere=NULL;
        }
        printf("\nRecording volume has been canceled");
    }
    else
    {
        printf("\nNew volume successfully added !!");
    }
    getch();

}

void contenu_reprt_volume(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud2;
    pile *k;
    int stop=0;
    int nbrelem=0;
    int nbrreprt=0;
    int nbrfich=0;
    int nbrfils;
    char chem[100];
    char chem2[100];
    pile *ppp=(pile*)malloc(sizeof(pile));
    liste_rep *lrep=NULL;

    chemin *first=NULL,*last,*elem,*ptr;
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nGive the path of a volume or repertory you want to display its contents : \n");
    gets(chem);
    strcpy(chem2,chem);

    noeud=chercher_elem(chem,rac);

    if(noeud==NULL)
    {
        printf("This path is wrong!!");
        getch();
    }
    else
    {
        if(noeud->type=='f'||noeud->type=='d')
        {
            if(noeud->type=='f')
                printf("\nThis is the path to a file and not volume or repertory !!");
            else
                printf("\nThis is the path to your disk and not volume or repertory !!");
            getch();
        }
        else
        {
            if(noeud->fils==NULL)
            {
                if(noeud->type=='v')
                    printf("\nThis volume is empty !! ");
                else
                    printf("\nthis repertory is empty!! ");

                getch();
            }
            else
            {
                if(noeud->type=='v')
                    printf("\nWe find in this volume the following elements : ");
                else
                    printf("\nWe find in this repertory the following elements : ");

                nbrfils=0;
                noeud2=noeud->fils;

                while(noeud2!=NULL)
                {
                    nbrfils++;
                    printf("\n%s\t: ",noeud2->nom);
                    printf("%s\\",chem2);
                    printf("%s",noeud2->nom);
                    noeud2=noeud2->frere;
                }

                if(noeud->type=='v')
                    printf("\n\nWe find from this volume the following elements : ");
                else
                    printf("\n\nWe find from this repertory the following elements : ");

                noeud2=noeud->fils;

                do
                {
                    nbrelem++;

                    if(noeud2->type=='f')
                        nbrfich++;
                    else
                        nbrreprt++;

                    printf("\n%s\t: %s\\",noeud2->nom,chem2);

                    if(noeud2->fils==NULL)
                    {
                        ptr=first;
                        while(ptr!=NULL)
                        {
                            printf("%s\\",ptr->contenu);
                            ptr=ptr->suiv;
                        }
                        printf("%s",noeud2->nom);

                    }

                    if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
                    {
                        ppp=Empiler(ppp,noeud2);
                    }

                    if(noeud2->fils!=NULL)
                    {
                        elem=(chemin*)malloc(sizeof(chemin));
                        strcpy(elem->contenu,noeud2->nom);
                        elem->suiv=NULL;

                        if(first==NULL)
                        {
                            first=elem;
                            last=elem;
                        }
                        else
                        {
                            last->suiv=elem;
                            last=elem;
                        }

                        ptr=first;

                        while(ptr!=NULL)
                        {
                            if(ptr->suiv==NULL)
                                printf("%s",ptr->contenu);
                            else
                                printf("%s\\",ptr->contenu);

                            ptr=ptr->suiv;
                        }

                        noeud2=noeud2->fils;
                    }
                    else
                    {
                        if(noeud2->frere!=NULL)
                        {
                            noeud2=noeud2->frere;
                        }
                        else
                        {

                            if(EstVide(ppp)!=1)
                            {
                                noeud2=ppp->elm->frere;
                                k=ppp;
                                ppp=ppp->bas;
                                free(k);
                            }
                            else
                            {
                                k=ppp;
                                ppp=ppp->bas;
                                free(k);
                                stop=1;
                            }

                            if(first!=NULL)
                            {
                                if(first==last)
                                {
                                    first=NULL;
                                    last=NULL;
                                    free(ptr);
                                }
                                else
                                {
                                    ptr=first;

                                    while(ptr->suiv!=last)
                                    {
                                        ptr=ptr->suiv;
                                    }
                                    last=ptr;
                                    free(ptr->suiv);
                                    last->suiv=NULL;
                                }
                            }
                        }
                    }
                }
                while(stop!=1);

                if(noeud->type=='v')
                {
                    printf("\n\nNumber of threads in this volume\t\t\t     : %d",nbrfils);
                    printf("\nTotal number of all elements from this volume onwards           : %d",nbrelem);
                    printf("\nTotal number of all files from this volume                    : %d",nbrfich);
                    printf("\nTotal number of all directories from this volume onwards   : %d",nbrreprt);
                }
                else
                {
                    printf("\n\nNumber of threads in this repertory\t\t\t\t : %d",nbrfils);
                    printf("\nTotal number of all items in this repertory             : %d",nbrelem);
                    printf("\nTotal number of all files from this repertory                    : %d",nbrfich);
                    printf("\nTotal number of all repertories from this repertory              : %d",nbrreprt);
                }
                printf("\n\nPress any key to continue");
                getch();
            }
        }
    }

}

void contenu_disque(elem_arbre *rac)
{
    elem_arbre *noeud2;
    pile *k;
    int stop=0;
    int nbrelem=0;
    int nbrreprt=0;
    int nbrfich=0;
    int nbrfils;
    char nom2[10];

    pile *ppp=(pile*)malloc(sizeof(pile));

    chemin *first=NULL,*last,*elem,*ptr,*rrr;
    ppp->elm=NULL;
    ppp->bas=NULL;


    printf("\n\nThis disk contains the following elements : ");

    nbrfils=0;
    noeud2=rac->fils;

    while(noeud2!=NULL)
    {
        nbrfils++;
        printf("\n%s\t: ",noeud2->nom);
        printf("%s\\",rac->nom);
        printf("%s",noeud2->nom);
        noeud2=noeud2->frere;
    }

    printf("\n\nFrom this disk we find the following elements : ");

    noeud2=rac->fils;


    do
    {
        nbrelem++;

        if(noeud2->type=='f')
            nbrfich++;
        else
        {
            if(noeud2->type=='r')
                nbrreprt++;
        }

        printf("\n%s\t: %s\\",noeud2->nom,rac->nom);

        if(noeud2->fils==NULL)
        {
            ptr=first;
            while(ptr!=NULL)
            {
                printf("%s\\",ptr->contenu);
                ptr=ptr->suiv;
            }
            printf("%s",noeud2->nom);

        }

        if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud2);
        }

        if(noeud2->fils!=NULL)
        {
            elem=(chemin*)malloc(sizeof(chemin));
            strcpy(elem->contenu,noeud2->nom);
            elem->suiv=NULL;

            if(first==NULL)
            {
                first=elem;
                last=elem;
            }
            else
            {
                last->suiv=elem;
                last=elem;
            }

            ptr=first;
            while(ptr!=NULL)
            {
                if(ptr->suiv==NULL)
                    printf("%s",ptr->contenu);
                else
                    printf("%s\\",ptr->contenu);

                ptr=ptr->suiv;
            }

            noeud2=noeud2->fils;
        }
        else
        {
            if(noeud2->frere!=NULL)
            {
                noeud2=noeud2->frere;
            }
            else
            {
                if(EstVide(ppp)!=1)
                {
                    strcpy(nom2,ppp->elm->nom);
                    noeud2=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

                if(first!=NULL&&stop!=1)
                {
                    if(first==last)
                    {
                        first=NULL;
                        last=NULL;
                        free(ptr);
                    }
                    else
                    {
                        ptr=first;

                        if(strcmp(ptr->contenu,nom2)==0)
                        {
                            while(ptr!=NULL)
                            {
                                rrr=ptr;
                                ptr=ptr->suiv;
                                free(rrr);
                            }

                            first=NULL;
                            last=NULL;
                        }
                        else
                        {
                            while(ptr!=NULL&&strcmp(ptr->suiv->contenu,nom2)!=0)
                            {
                                ptr=ptr->suiv;
                            }

                            if(ptr!=NULL)
                            {
                                last=ptr;
                                free(ptr->suiv);
                                last->suiv=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    while(stop!=1);

    printf("\n\nNumber of volume in this disk  \t\t\t\t     : %d",nbrfils);
    printf("\nTotal number of all elements from this disk                  : %d",nbrelem);
    printf("\nTotal number of all files from this disk                     : %d",nbrfich);
    printf("\nTotal number of all repertories from this disk               : %d",nbrreprt);

}


int existence_d_un_elem_ds_un_volrprt(elem_arbre*rac,elem_arbre *elem_cherch)
{
    pile *k;
    int stop=0;
    pile *ppp=(pile*)malloc(sizeof(pile));
    elem_arbre *noeud2;
    ppp->elm=NULL;
    ppp->bas=NULL;



    noeud2=rac->fils;

    do
    {
        if(noeud2==elem_cherch)
            return 1;

        if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud2);
        }

        if(noeud2->fils!=NULL)
        {
            noeud2=noeud2->fils;
        }
        else
        {
            if(noeud2->frere!=NULL)
            {
                noeud2=noeud2->frere;
            }
            else
            {
                if(EstVide(ppp)!=1)
                {
                    noeud2=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }
            }
        }
    }
    while(stop!=1);

    return 0;
}

void nbr_occur_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud2;
    pile *k;
    int stop=0;
    int nbr_occur;
    char chem[100];
    char nom[10];
    char nom2[10];
    char chem2[100];
    liste_rep *lrep=NULL;

    pile *ppp=(pile*)malloc(sizeof(pile));

    chemin *first=NULL,*last,*elem,*ptr,*rrr;
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nGive the path of the element from which you want to check \nthe existence of your element         : \n");
    gets(chem);
    strcpy(chem2,chem);

    noeud=chercher_elem(chem,rac);
    if(noeud==NULL)
    {
        printf("This path is wrong");
        getch();
    }
    else
    {
        if(noeud->type=='f')
        {
            printf("\nThis is the path to a file and not to a volume or repertory or \nto your main computer !!");
            getch();
        }
        else
        {
            if(noeud->fils==NULL)
            {
                if(noeud->type=='v')
                    printf("\nThis disk is empty !!");
                else
                    printf("\nthis repertory is empty !! ");

                getch();
            }
            else
            {
                printf("\nGive the name of the element to be searched : ");
                gets(nom);

                if(strcmp(nom,rac->nom)==0)
                {
                    printf("Please choose a name other than the name of your disc !!");
                }
                else
                {
                    nbr_occur=nbr_elem(rac,nom);
                    if(nbr_occur==0)
                    {
                        printf("\nThis element does not exist !!");
                        getch();
                    }
                    else
                    {
                        if(nbr_occur==1)
                        {
                            printf("\nThis element exists 1 time in the following address :");
                        }
                        else
                        {
                            printf("\nThis element exists %d times in the following addresses :",nbr_occur);
                        }


                        noeud2=noeud->fils;

                        do
                        {

                            if(strcmp(noeud2->nom,nom)==0)
                            {
                                printf("\n%s\t: %s\\",noeud2->nom,chem2);

                                if(noeud2->fils==NULL)
                                {
                                    ptr=first;
                                    while(ptr!=NULL)
                                    {
                                        printf("%s\\",ptr->contenu);
                                        ptr=ptr->suiv;
                                    }
                                    printf("%s",noeud2->nom);

                                }
                            }

                            if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
                            {
                                ppp=Empiler(ppp,noeud2);
                            }

                            if(noeud2->fils!=NULL)
                            {
                                elem=(chemin*)malloc(sizeof(chemin));
                                strcpy(elem->contenu,noeud2->nom);
                                elem->suiv=NULL;

                                if(first==NULL)
                                {
                                    first=elem;
                                    last=elem;
                                }
                                else
                                {
                                    last->suiv=elem;
                                    last=elem;
                                }

                                if(strcmp(noeud2->nom,nom)==0)
                                {
                                    ptr=first;
                                    while(ptr!=NULL)
                                    {
                                        if(ptr->suiv==NULL)
                                            printf("%s",ptr->contenu);
                                        else
                                            printf("%s\\",ptr->contenu);

                                        ptr=ptr->suiv;
                                    }
                                }

                                noeud2=noeud2->fils;
                            }
                            else
                            {
                                if(noeud2->frere!=NULL)
                                {
                                    noeud2=noeud2->frere;
                                }
                                else
                                {
                                    if(EstVide(ppp)!=1)
                                    {
                                        strcpy(nom2,ppp->elm->nom);
                                        noeud2=ppp->elm->frere;
                                        k=ppp;
                                        ppp=ppp->bas;
                                        free(k);
                                    }
                                    else
                                    {
                                        k=ppp;
                                        ppp=ppp->bas;
                                        free(k);
                                        stop=1;
                                    }

                                    if(first!=NULL&&stop!=1)
                                    {
                                        if(first==last)
                                        {
                                            first=NULL;
                                            last=NULL;
                                            free(ptr);
                                        }
                                        else
                                        {
                                            ptr=first;

                                            if(strcmp(ptr->contenu,nom2)==0)
                                            {
                                                while(ptr!=NULL)
                                                {
                                                    rrr=ptr;
                                                    ptr=ptr->suiv;
                                                    free(rrr);
                                                }

                                                first=NULL;
                                                last=NULL;
                                            }
                                            else
                                            {
                                                while(ptr!=NULL&&strcmp(ptr->suiv->contenu,nom2)!=0)
                                                {
                                                    ptr=ptr->suiv;
                                                }

                                                if(ptr!=NULL)
                                                {
                                                    last=ptr;
                                                    free(ptr->suiv);
                                                    last->suiv=NULL;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        while(stop!=1);

                        printf("\n\nPress any key to continue");

                        getch();
                    }
                }
            }

        }
    }

}

void copier_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud3,*p;
    pile *k;
    int stop=0,trouve;
    char chem[100];
    liste_rep *lrep=NULL;
    pile *ppp2=(pile*)malloc(sizeof(pile));
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;
    ppp2->elm=NULL;
    ppp2->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nGive the path of the element to be copied  : \n");
    gets(chem);

    noeud=chercher_elem(chem,rac);

    if(noeud==NULL)
    {
        printf("This path is wrong !!");
        getch();
    }
    else
    {
        if(noeud->type=='d')
        {
            printf("This is the path to your disk and not to a File or repertory or Volume. !!");
            getch();
        }
        else
        {
            printf("\nGive the path of a volume or directory into which you want \ncto copy the element : \n");
            gets(chem);

            noeud3=chercher_elem(chem,rac);
            if(noeud3==NULL)
            {
                printf("This path is wrong  !!");
                getch();
            }
            else
            {
                if(noeud3->type=='f')
                {
                    printf("It is impossible to make the copy because it is the path to a file !!");
                    getch();

                }
                else
                {

                    if(noeud3==noeud)
                    {
                        printf("It is impossible to make the copy because it is the same path !!");
                        getch();
                    }
                    else
                    {
                        if((noeud->type=='r'||noeud->type=='v')&&noeud->fils!=NULL&&existence_d_un_elem_ds_un_volrprt(noeud,noeud3)==1)//on cherche le quoi à copier dans le ou emplacement
                        {
                            printf("It is not possible to copy a main content into its sub content !!");
                            getch();
                        }
                        else
                        {
                            trouve=0;

                            for(p=noeud3->fils; p!=NULL&&strcmp(p->nom,noeud->nom)!=0; p=p->frere);

                            if(p!=NULL)
                                trouve=1;


                            if(trouve==1)
                            {
                                printf("It is impossible to make the copy because in this location there is \nan element with the same name as the one to be copied !!");
                                getch();
                            }
                            else
                            {
                                if(noeud3->fils==NULL)
                                {
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;
                                }
                                else
                                {
                                    noeud3=noeud3->fils;

                                    while(noeud3->frere!=NULL)
                                    {
                                        noeud3=noeud3->frere;
                                    }

                                    noeud3->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->frere->nom,noeud->nom);
                                    noeud3->frere->frere=NULL;
                                    noeud3->frere->fils=NULL;
                                    noeud3->frere->type=noeud->type;
                                    noeud3=noeud3->frere;
                                }

                                if(noeud->type=='r'&&noeud->fils!=NULL)
                                {

                                    noeud=noeud->fils;
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;

                                    do
                                    {
                                        if(noeud->fils!=NULL&&noeud->frere!=NULL)
                                        {
                                            ppp=Empiler(ppp,noeud);
                                            ppp2=Empiler(ppp2,noeud3);
                                        }

                                        if(noeud->fils!=NULL)
                                        {
                                            noeud=noeud->fils;
                                            p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                            strcpy(p->nom,noeud->nom);
                                            p->frere=NULL;
                                            p->fils=NULL;
                                            p->type=noeud->type;
                                            noeud3->fils=p;
                                            noeud3->frere=NULL;
                                            noeud3=noeud3->fils;

                                        }
                                        else
                                        {
                                            if(noeud->frere!=NULL)
                                            {
                                                noeud=noeud->frere;
                                                p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                strcpy(p->nom,noeud->nom);
                                                p->frere=NULL;
                                                p->fils=NULL;
                                                p->type=noeud->type;
                                                noeud3->frere=p;
                                                noeud3->fils=NULL;
                                                noeud3=noeud3->frere;
                                            }
                                            else
                                            {
                                                if(EstVide(ppp)!=1)
                                                {
                                                    noeud=ppp->elm->frere;
                                                    noeud3=ppp2->elm;

                                                    p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                    strcpy(p->nom,ppp->elm->frere->nom);
                                                    p->frere=NULL;
                                                    p->fils=NULL;
                                                    p->type=ppp->elm->type;
                                                    noeud3->frere=p;
                                                    noeud3=noeud3->frere;

                                                    k=ppp;

                                                    ppp=ppp->bas;

                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                }
                                                else
                                                {
                                                    k=ppp;
                                                    ppp=ppp->bas;
                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                    stop=1;
                                                }
                                            }
                                        }
                                    }
                                    while(stop!=1);
                                }

                                printf("Your element has been successfully copied !!");

                                printf("\n");
                                afficher_itter(*rac,lrep);
                                printf("\n");
                                printf("Press any key to continue");
                                getch();
                            }
                        }
                    }
                }
            }
        }
    }
}

void deplacer_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud3,*p;
    pile *k;
    int stop=0,trouve;
    char chem[100];
    char chem3[100];
    liste_rep *lrep=NULL;
    pile *ppp2=(pile*)malloc(sizeof(pile));
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp2->elm=NULL;
    ppp2->bas=NULL;

    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nGive the path of the element to be moved : \n");
    gets(chem);
    strcpy(chem3,chem);

    noeud=chercher_elem(chem,rac);


    if(noeud==NULL)
    {
        printf("This path is wrong !!");
        getch();
    }
    else
    {
        if(noeud->type=='d')
        {
            printf("This is the path to your disk and not to a File or repertory or Volume !!");
            getch();
        }
        else
        {
            printf("\nGive the path of a volume or directory in which you want \nto move the element : \n");
            gets(chem);
            noeud3=chercher_elem(chem,rac);

            if(noeud3==NULL)
            {
                printf("This path is wrong !!");
                getch();
            }
            else
            {
                if(noeud3->type=='f')
                {
                    printf("It is impossible to make the move because it is the path of a file !!");
                    getch();
                }
                else
                {

                    if(noeud3==noeud)
                    {
                        printf("It is impossible to make the trip because it is the same way !!");
                        getch();
                    }
                    else
                    {
                        if((noeud->type=='r'||noeud->type=='v')&&noeud->fils!=NULL&&existence_d_un_elem_ds_un_volrprt(noeud,noeud3)==1)//on cherche le quoi à copier dans le ou emplacement
                        {
                            printf("It is impossible to move a main content into its sub content !!");
                            getch();
                        }
                        else
                        {


                            trouve=0;

                            for(p=noeud3->fils; p!=NULL&&strcmp(p->nom,noeud->nom)!=0; p=p->frere);

                            if(p!=NULL)
                                trouve=1;

                            if(trouve==1)
                            {
                                printf("It is impossible to make the move because in this location there is \nan element with the same name as the one to be moved !!");
                                getch();
                            }
                            else
                            {


                                if(noeud3->fils==NULL)
                                {
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;
                                }
                                else
                                {
                                    noeud3=noeud3->fils;

                                    while(noeud3->frere!=NULL)
                                    {
                                        noeud3=noeud3->frere;
                                    }

                                    noeud3->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->frere->nom,noeud->nom);
                                    noeud3->frere->frere=NULL;
                                    noeud3->frere->fils=NULL;
                                    noeud3->frere->type=noeud->type;
                                    noeud3=noeud3->frere;
                                }

                                if(noeud->type=='r'&&noeud->fils!=NULL)
                                {

                                    noeud=noeud->fils;
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;

                                    do
                                    {
                                        if(noeud->fils!=NULL&&noeud->frere!=NULL)
                                        {
                                            ppp=Empiler(ppp,noeud);
                                            ppp2=Empiler(ppp2,noeud3);
                                        }

                                        if(noeud->fils!=NULL)
                                        {
                                            noeud=noeud->fils;
                                            p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                            strcpy(p->nom,noeud->nom);
                                            p->frere=NULL;
                                            p->fils=NULL;
                                            p->type=noeud->type;
                                            noeud3->fils=p;
                                            noeud3->frere=NULL;
                                            noeud3=noeud3->fils;

                                        }
                                        else
                                        {
                                            if(noeud->frere!=NULL)
                                            {
                                                noeud=noeud->frere;
                                                p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                strcpy(p->nom,noeud->nom);
                                                p->frere=NULL;
                                                p->fils=NULL;
                                                p->type=noeud->type;
                                                noeud3->frere=p;
                                                noeud3->fils=NULL;
                                                noeud3=noeud3->frere;
                                            }
                                            else
                                            {
                                                if(EstVide(ppp)!=1)
                                                {
                                                    noeud=ppp->elm->frere;
                                                    noeud3=ppp2->elm;

                                                    p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                    strcpy(p->nom,ppp->elm->frere->nom);
                                                    p->frere=NULL;
                                                    p->fils=NULL;
                                                    p->type=ppp->elm->type;
                                                    noeud3->frere=p;
                                                    noeud3=noeud3->frere;

                                                    k=ppp;

                                                    ppp=ppp->bas;

                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                }
                                                else
                                                {
                                                    k=ppp;
                                                    ppp=ppp->bas;
                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                    stop=1;
                                                }
                                            }
                                        }
                                    }
                                    while(stop!=1);
                                }

                                supprimer_elem_couper(rac,chem3);
                                printf("Your element has been moved successfully !!");
                                printf("\n");
                                afficher_itter(*rac,lrep);
                                printf("\n");
                                printf("\nPress any key to continue");
                                getch();
                            }
                        }
                    }
                }
            }
        }
    }

}

void renommer(elem_arbre *rac)
{
    char chem[100],nom[10];
    elem_arbre*noeud;
    int repeter;
    liste_rep *lrep=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");
    printf("\nGive the path of the element you want to rename : \n");
    gets(chem);

    noeud=chercher_elem(chem,rac);


    if(noeud==NULL)
    {
        printf("This path is wrong !!");
        getch();
    }
    else
    {
        do
        {
            printf("Give the new name : ");
            gets(nom);
            repeter=redandonce_nom(rac,noeud,nom);
            if(repeter==1)
                printf("It is better to change your name please !!");
        }
        while(strcmp(nom,"\0")==0||repeter==1);

        strcpy(noeud->nom,nom);

        printf("Successful modification !!");

        printf("\n");
        afficher_itter(*rac,lrep);
        printf("\n");

        printf("\nPress any key to continue");
        getch();

    }

}

void titre(void)
{
    printf("                         -------------------------------------------------------\n");
    printf("                        |                   ~~ ARBO-GV ~~                       |\n");
    printf("                        |         TREE PROGRAM AND VOLUME MANAGEMENT            |\n");
    printf("                         -------------------------------------------------------\n");
}

void introduction(void)
{
    printf("\n\n\n\t\t\t\t       Hello (^_^) !!\n\t Here is a volume management program that allows you to view and manage your drive \n                                            the way you want\n ");
    printf("\t                                Press any key to begin ");

    getch();
}

int menu_prin(elem_arbre rac)
{
    int boucle=1,rep;

    clrscr();

    titre();


    printf(" \n                                 --------------------------------------\n");
    printf("                                |           Main menu                  |\n");
    printf("                                 --------------------------------------\n");
    printf("                                |   1 . Add a volume                   |\n");;
    printf("                                |   2 . Manage your disk               |\n");
    printf("                                |   3 . Display the list of volumes    |\n");
    printf("                                |   4 . Exit                           |\n");
    printf("                                 --------------------------------------\n");
    do
    {
        printf("\t\t\t\t\t\t    Your choice : ");
        rep=getch();


        if(rep!=49&&rep!=50&&rep!=51&&rep!=52)
        {
            printf("\nPlease make a choice between 1 and 4 !!\n");
            boucle=1;
        }
        else
        {
            if(rac.fils!=NULL)
            {
                boucle=0;
            }
            else
            {
                if(rep==50||rep==51)
                    printf("\nYou must add at least one volume first !!\n");
                else
                    boucle=0;
            }
        }
    }
    while(boucle==1);



    return rep;
}

int menu_gest_disque(void)
{
    int rep;

    clrscr();

    titre();

    printf(" \n                            -------------------------------------------------\n");
    printf("                           |                DISK MANAGEMENT                  |\n");
    printf("                            -------------------------------------------------\n");
    printf("                           |   1 . Add a new element (R/F)                     |\n");
    printf("                           |   2 . Display the content of an element (V/R)     |\n");
    printf("                           |   3 . Copy an element (V/R/F)                     |\n");
    printf("                           |   4 . Moving an element (V/R/F)                   |\n");
    printf("                           |   5 . Rename an element (D/V/R/F)                 |\n");
    printf("                           |   6 . Delete an element (D/V/R/F)                 |\n");
    printf("                           |   7 . Number of occurrences of an element (V/R/F) |\n");
    printf("                            -------------------------------------------------\n");

    printf("\nR : back to main menul\n");
    printf("your choice : ");

    do
    {
        rep=getch();
    }
    while(rep!=49&&rep!=50&&rep!=51&&rep!=52&&rep!=53&&rep!=54&&rep!=55&&rep!=114&&rep!=82);

    return rep;
}

int main()
{
    elem_arbre *rac;
    liste_rep *lrep=NULL;
    int choix1=-1,choix2;

    titre();
    introduction();
    rac=initialiser(rac);

    do
    {
        switch (choix1)
        {
        case -1 :
            choix1=menu_prin(*rac);
            break;

        case 49 :
            ajouter_vol(rac);
            choix1=-1;
            break;
        case 51 :
            printf("\n");
            afficher_itter(*rac,lrep);
            contenu_disque(rac);
            printf("\n\nPress any key to continue ");
            getch();
            choix1=-1;
            break;
        case 50 :
        {
            choix2=menu_gest_disque();
            switch (choix2)
            {
            case 49 :
                ajouter_nv_elem(rac);
                choix1=50;
                break;
            case 50 :
                contenu_reprt_volume(rac);
                choix1=50;
                break;
            case 51 :
                copier_elem(rac);
                choix1=50;
                break;
            case 52 :
                deplacer_elem(rac);
                choix1=50;
                break;
            case 53 :
                renommer(rac);
                choix1=50;
                break;
            case 54 :
                supprimer_elem(rac);
                if(rac->fils==NULL)
                    choix1=-1;
                else
                    choix1=50;
                break;
            case 55 :
                nbr_occur_elem(rac);
                choix1=50;
                break;
            case 82 :
                choix1=-1;
                break;
            case 114:
                choix1=-1;
                break;

            }
        }
        }
    }
    while(choix1!=52);

    printf("\n\n\t\t      Thank you for using this program (^_^) see you soon !!\n\n");
    getch();

    return 0;
}
