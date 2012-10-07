#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <QtGui>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::base_start();

}

int MainWindow::rechercheLettre(QString lettre)
{
    int i = 0;
    int bonneLettre = 0;
    QString motSecret;
    motSecret = ui->mot_pioch->text();
    QString mot_etoile;
    mot_etoile = ui->label->text();
    QString mot;

    // On parcourt motSecret pour vérifier si la lettre proposée y est
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        mot = motSecret[i];
       // QMessageBox::critical(this, "fff", mot);
        if (mot == lettre) // Si la lettre y est
        {

                // QMessageBox::critical(this,"lettre ok ","lettre oj !");
                 bonneLettre = 1; // On mémorise que c'était une bonne lettre
                // lettreTrouvee[i] = 1; // On met à 1 le case du tableau de booléens correspondant à la lettre actuelle
                 mot_etoile.replace(i,1, lettre);
               //  QMessageBox::critical(this,"ddd",mot_etoile);
        }

        ui->label->setText(mot_etoile);
    }

    return bonneLettre;
}

int MainWindow::gagne(QString mot_etoile)
{
    long i = 0;
    int joueurGagne = 1;
    int tailleMot = mot_etoile.size();
    QString lettre;
    lettre = "*";
    QString mot;
   /* for (i = 0 ; i < tailleMot; i++)
    {
        mot = mot_etoile[i];
        if (mot == lettre) // Si la lettre y est
        {

        }

        ui->label->setText(mot_etoile);
    }
   for (i = 0 ; i < tailleMot ; i++)
    {
        mot = mot_etoile[i];
        if (mot == "*")
            joueurGagne = 0;
    }*/

    return joueurGagne;
}

void MainWindow::on_touche_clicked()
{
    int tent = ui->tent->text().toInt();
    tent++;
    ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche->text();
    int ok ;
    ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }



}

void MainWindow::on_touche_2_clicked()
{
    int tent = ui->tent->text().toInt();
    tent++;
    ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_2->text();
   int ok = MainWindow::rechercheLettre(lett);

    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_3_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_3->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_4_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_4->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_5_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_5->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }

}

void MainWindow::on_touche_6_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_6->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_7_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_7->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_8_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_8->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_10_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_10->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_11_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_11->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_12_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_12->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_13_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_13->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_14_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_14->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_15_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_15->text();
  int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_16_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_16->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_17_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_17->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_18_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_18->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_19_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_19->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_20_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_20->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_21_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_21->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}


void MainWindow::on_touche_22_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_22->text();
    int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_23_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_23->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_24_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_24->text();
   int ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

void MainWindow::on_touche_9_clicked()
{    int tent = ui->tent->text().toInt();
     tent++;
     ui->tent->setText(QString::number(tent));
    QString lett;
    lett = ui->touche_9->text();
  int  ok = MainWindow::rechercheLettre(lett);
    if (ok == 1)
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
    }
    else
    {
        QString listelettre;
        listelettre = ui->lettres->text();
        listelettre += lett;
        ui->lettres->setText(listelettre);
        MainWindow::AfficherPendu();
      //  QMessageBox::critical(this, "", "");
    }
}

QString MainWindow::TrouverMot()
{
    int MAX = 0;
    char caractere = 0;

    QFile filz("dico.txt");

    if (!filz.open(QIODevice::ReadOnly))
        return ("ERROR");
    QTextStream fichier(&filz);

    // Compte du nombre de mots
    while (!fichier.atEnd())
    {
        fichier >> caractere;

        if (caractere == '\n')
            MAX++;
    }

    fichier.seek(0);

    // Definition du nombre aléatoire
    // et positionnement dans le fichier
    int ligneAleat = rand() % MAX;
    int t = 0;

    while (t != ligneAleat)
    {
        fichier >> caractere;
        if (caractere == '\n')
            t++;
    }

    // Retour du mot selectionné
    QString mot;
    fichier >> mot;
    MainWindow::TrouverTraduct(ligneAleat);
   // QMessageBox::information(this, "bla", mot);

    return mot;
}

QString MainWindow::TrouverTraduct(int ligne)
{
   // ui->txt_trad->hide();

    int MAX = 0;
    char caractere = 0;

    QFile filz("trad.txt");

    if (!filz.open(QIODevice::ReadOnly))
        return ("ERROR");
    QTextStream fichier(&filz);

    // Compte du nombre de mots
    while (!fichier.atEnd())
    {
        fichier >> caractere;

        if (caractere == '\n')
            MAX++;
    }

    fichier.seek(0);

    // Definition du nombre aléatoire
    // et positionnement dans le fichier
    int t = 0;

    while (t != ligne)
    {
        fichier >> caractere;
        if (caractere == '\n')
            t++;
    }

    // Retour du mot selectionné
    QString mot;
    fichier >> mot;
    //QMessageBox::information(this, "bla", mot);
    ui->txt_trad->setText(mot);
    return mot;
}


int MainWindow::nombreAleatoire(int nombreMax)
{
        srand(time(NULL));
        return (rand() % nombreMax);
}

void MainWindow::on_actionNouveau_Mot_triggered()
{
    MainWindow::base_start();

}

void MainWindow::on_actionAfficher_le_dictionaire_triggered()
{

}


void MainWindow::on_actionQuitter_triggered()
{
    MainWindow::close();
}

void MainWindow::base_start()
{
    QString motSecret; // Ce sera le mot à trouver
    int *lettreTrouvee = NULL; // Un tableau de booléens. Chaque case correspond à une lettre du mot secret. 0 = lettre non trouvée, 1 = lettre trouvé
    long i = 0; // Une petite variable pour parcourir les tableaux
    long tailleMot = 0;
    ui->mot_pioch->hide();
    ui->lettres->setText("");
    ui->png_number->setText("0");
    ui->png->hide();
    ui->png_2->hide();
    ui->png_3->hide();
    ui->png_4->hide();
    ui->png_5->hide();
    ui->png_6->hide();
    ui->png_7->hide();
    ui->png_8->hide();
    ui->png_9->hide();
    ui->png_10->hide();
    ui->png_11->hide();
    ui->png_number->hide();



    motSecret = MainWindow::TrouverMot();
    ui->mot_pioch->setText(motSecret);

    tailleMot = motSecret.size();
   // QMessageBox::critical(this, "bla", QString::number(tailleMot));
    lettreTrouvee = new int[tailleMot]; // On alloue dynamiquement le tableau lettreTrouvee (dont on ne connaissait pas la taille au départ)
        if (lettreTrouvee == NULL)
            exit(0);

     QString mot_etoile;
     for (i = 0 ; i < tailleMot ; i++)
     {
          lettreTrouvee[i] = 0;
          //QMessageBox::critical(this, "bla", QString::number(i));
          mot_etoile += "*";

     }
     ui->label->setText(mot_etoile);



}

void MainWindow::AfficherPendu()
{
    int pos_actu = ui->png_number->text().toInt();
    pos_actu++;
    ui->png_number->setText(QString::number(pos_actu));
    switch(pos_actu)
    {
    case 1 :
        ui->png->show();
        break;
    case 2 :
        ui->png_2->show();
        break;
    case 3 :
        ui->png_3->show();
        break;
    case 4 :
        ui->png_4->show();
        break;
    case 5 :
        ui->png_5->show();
        break;
    case 6 :
        ui->png_6->show();
        break ;
    case 7 :
        ui->png_7->show();
        break ;
    case 8 :
        ui->png_8->show();
        break ;
    case 9 :
        ui->png_9->show();
        break ;
    case 10 :
        ui->png_10->show();
        break ;
    case 11 :
        ui->png_11->show();
        QMessageBox::critical(this, "vous estes Mort !", "vous avez perdu...\n vous etes pendu ...");
        MainWindow::base_start();
        break ;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
