#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <QtGui>
#include <QtSql>
#include <QTcpSocket>
#include <QNetworkReply>
#include <iostream>
#include <fstream>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BoutonQuitter->hide();
    ui->BoutonRejouer->hide();
    ui->FenPendu->hide();
    ui->FenResultat->hide();
    ui->FenScore->hide();
    ui->FenOptions->hide();
    ui->TxtSansFautes->hide();
    ui->NomUserPendu->hide();
    ui->BoutonRetour->hide();
    ui->MotPioche->hide();
    ui->NomImg->hide();
    ui->TempsRestant->hide();
    ui->TxtNiveau->hide();
    ui->TxtMotPerdu->hide();
    ui->FenMultiplayer->hide();
    ui->FenInscription->hide();
    ui->FenInfoMulti->hide();
    ui->FenInvitation->setEnabled(false);
    ui->FenEnvoiInvitation->hide();
    ui->FenReceveurInv->hide();
    ui->BoutonJouerMultiplayerEnvoi->setEnabled(false);
    ui->BoutonJouerMultiplayerRecev->setEnabled(false);
    ui->FenPenduMultiplayer->hide();

    ui->BoutonConnection->setShortcut(QKeySequence(Qt::Key_Return));

    TypesDonneesRecues = 0;
    TypesFermeture = 0;

    ui->png_1->setPixmap(QPixmap("images/1.png"));
    ui->png_2->setPixmap(QPixmap("images/2.png"));
    ui->png_3->setPixmap(QPixmap("images/3.png"));
    ui->png_4->setPixmap(QPixmap("images/4.png"));
    ui->png_5->setPixmap(QPixmap("images/5.png"));
    ui->png_6->setPixmap(QPixmap("images/6.png"));
    ui->png_7->setPixmap(QPixmap("images/7.png"));
    ui->png_8->setPixmap(QPixmap("images/8.png"));
    ui->png_9->setPixmap(QPixmap("images/9.png"));
    ui->png_10->setPixmap(QPixmap("images/10.png"));
    ui->png_11->setPixmap(QPixmap("images/11.png"));

    setWindowTitle("LePendu - V1");
    setWindowIcon(QIcon("images/icone.png"));

    QFile ImgFondExist("images/img.png");

    if(ImgFondExist.exists())
    {
        QPalette palette;
        QImage img("images/img.png");
        palette.setBrush(this->backgroundRole(), QBrush(img));
        this->setPalette(palette);
    }
    else
    {
        QPalette palette;
        QImage img("images/fond.jpg");
        palette.setBrush(this->backgroundRole(), QBrush(img));
        this->setPalette(palette);
    }

    QFile fichier_option_pendu("config.ini");

    if(fichier_option_pendu.exists())
    {
        QSettings options("config.ini", QSettings::IniFormat);

        ui->NomUser->setText(QString(options.value("utilisateur").toString()));

        if(options.value("modehorsligne") == true)
        {
            ui->FenMultiplayer->setEnabled(false);
        }
        else
        {
            ui->FenMultiplayer->setEnabled(true);

            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("mysql2.alwaysdata.com");
            db.setUserName("loquii");
            db.setPassword("lemondeducraft");
            db.setDatabaseName("loquii_pendu");

            if(query_base = new QSqlQuery(db))
            {

            }
            else
            {
                QMessageBox::critical(this,"Erreur","Nous n'arrivons pas à vous connecter à la base de donnée \n Etes-vous connecté ?");
            }
        }
    }
    else
    {
        QSettings options("config.ini", QSettings::IniFormat);

        options.setValue("utilisateur", "");
        options.setValue("dernierscore", "");
        options.setValue("nombrepartie", "0");
        options.setValue("niveau", "facile");
        options.setValue("indice", true);
        options.setValue("versionprogramme", "1");
        options.setValue("modehorsligne", true);
        options.setValue("police", "MS Shell");
        options.setValue("messagebienvenue", "");
    }

    QSettings options("config.ini", QSettings::IniFormat);

    ui->NombreParties->setText(QString(options.value("nombrepartie").toString()));

    /*QFont policethis = options.value("police");
    this->setFont(policethis);
    ui->NomPolice->setText(options.value("police"));*/

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerFin()));

    timer2 = new QTimer(this);
    timer2->setSingleShot(false);
    connect(timer2, SIGNAL(timeout()), this, SLOT(LancerPendu()));
}

void MainWindow::on_BoutonJouer_clicked()
{
    if(ui->NomUser->text() == "")
    {
        QMessageBox::critical(this,"Erreur","Vous devez renseigner un nom d'utilisateur");
    }
    else
    {
        MainWindow::Depart();
    }
}

void MainWindow::on_BoutonRejouer_clicked()
{
    MainWindow::Depart();
}

void MainWindow::on_BoutonMultiplayer_clicked()
{
    ui->FenPendu->hide();
    ui->GroupBoxScore->hide();
    ui->FenScore->hide();
    ui->FenMenu->hide();
    ui->FenOptions->hide();
    ui->FenMultiplayer->show();
    ui->BoutonRetour->show();
    ui->pseudo->setFocus();
}

void MainWindow::on_BoutonConnection_clicked()
{
    TypesFermeture = 2;
    ui->TxtStatut->setText("Connexion en cours ...");

    if (ui->pseudo->text() == "" || ui->mdp->text() == "")
        {
            QMessageBox::critical(this,"Erreur","Vous devez remplir des identifiants");

            ui->TxtStatut->clear();
        }
        else
        {

        QString mdp = ui->mdp->text();
        string pseudo_con = ui->pseudo->text().toStdString();
        QByteArray ba = QCryptographicHash::hash(mdp.toUtf8(), QCryptographicHash::Sha1); // on la hache
        QString mdp_hache=ba.toHex(); // on convertit le hash en QString

        if (db.open())
            {
                    QString requette_connection;
                    requette_connection = QString("SELECT * FROM user WHERE pseudo='") + ui->pseudo->text() + QString("'");

                    if(query_base->exec(requette_connection))
                    {
                        while(query_base->next())
                                   {

                                       for(int x=0; x < 1; ++x)
                                       {
                                           QSettings ident("ident.ident", QSettings::IniFormat);

                                           ident.setValue("pseudo", query_base->record().value("pseudo").toString());
                                           ident.setValue("motdepasse", query_base->record().value("mdp").toString());
                                           ident.setValue("email", query_base->record().value("email").toString());
                                           ident.setValue("age", query_base->record().value("age").toString());
                                           ident.setValue("pays",  query_base->record().value("pay").toString());
                                           ident.setValue("email_check", query_base->record().value("am_check").toString());
                                           ident.setValue("imagepersonnelle", query_base->record().value("img_name").toString());
                                           ident.setValue("messagepersonnel", query_base->record().value("msg_perso").toString());
                                       }
                                   }

                                    QSettings ident("ident.ident", QSettings::IniFormat);

                                        if(ident.value("pseudo").toString() == "" && ident.value("motdepasse").toString() == "")
                                        {
                                             QMessageBox::critical(this,"Erreur","Vous n'êtes pas inscrit");

                                             QProcess::execute("cmd /c start http://loquii.alwaysdata.net/desktop/#p=sub.html");

                                             ui->pseudo->clear();
                                             ui->mdp->clear();
                                             ui->TxtStatut->clear();
                                        }
                                        else
                                        {

                                                if (mdp_hache.toStdString() == ident.value("motdepasse").toString().toStdString() && pseudo_con == ident.value("pseudo").toString().toStdString())
                                                {
                                                    ui->NomUserMultiplayer->setText(ui->pseudo->text());
                                                    ui->TxtStatut->setText("Chargement des données ...");
                                                    ui->pseudo->clear();
                                                    ui->mdp->clear();
                                                    ui->TxtStatut->clear();
                                                    ui->BoutonRetour->hide();
                                                    ui->FenMultiplayer->hide();
                                                    ui->FenInfoMulti->show();

                                                    socket = new QTcpSocket(this);
                                                    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
                                                    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
                                                    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
                                                    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

                                                    MainWindow::on_BoutonActuServ_clicked();

                                                    MainWindow::ActuListeContact();
                                                }
                                                else
                                                {
                                                    QMessageBox::critical(this, "Erreur",tr("Votre identifiant ou mot de passe est incorect\nVous etes peut etre pas encore inscrit !"));

                                                    ui->mdp->clear();
                                                }
                                        }
                                    }
                                    else
                                    {
                                            QMessageBox::critical(this,"Erreur",tr("Une erreur est présente, merci de contacter le developpeur."));
                                    }

            db.close();
            }
            else
            {
                QMessageBox::critical(this,"Erreur",tr("Une erreur est présente, merci de contacter le developpeur. BDD"));
            }
    }
}

void MainWindow::on_BoutonActuServ_clicked()
{
    tailleMessage = 0;

    ui->TxtStatutServeur->setText(tr("<em>Connexion ...</em>"));

    socket->abort();
    socket->connectToHost("localhost", 50885);
    //"ftp-kiwiiserveur.serveftp.com"
}

void MainWindow::connecte()
{
    ui->TxtStatutServeur->setText("Connecté !");
}

void MainWindow::deconnecte()
{
    ui->TxtStatutServeur->setText("Deconnecté !");
}

void MainWindow::donneesRecues()
{
        QDataStream in(socket);

        if (tailleMessage == 0)
        {
            if (socket->bytesAvailable() < (int)sizeof(quint16))
                 return;

            in >> tailleMessage;
        }

        if (socket->bytesAvailable() < tailleMessage)
            return;

        QString messageRecu;
        in >> messageRecu;

        qDebug() << messageRecu;
        ui->TxtDonneesRecues->setText(messageRecu);

        if (messageRecu.contains("demande", Qt::CaseSensitive))
        {
            MainWindow::ActuInv();
        }

        if(TypesDonneesRecues == 1)
        {
            if (messageRecu.contains("oui", Qt::CaseSensitive))
            {
                qDebug() << "oui !!!!";
                qDebug() << NomUserInv;
                if(messageRecu.contains(NomUserInv, Qt::CaseSensitive))
                {
                    qDebug() << "yes !!!!";
                    timer->stop();

                    ui->TxtOkInvAccept->setText("Ok");
                    ui->TxtOkInvChargement->setText("...");

                    TypesDonneesRecues = 2;

                    timer2->start(1000);
                }
            }
            if(messageRecu.contains("non", Qt::CaseSensitive))
            {
                if(messageRecu.contains(NomUserInv, Qt::CaseSensitive))
                {
                    timer->stop();

                    ui->TxtOkInvAccept->setText("Non");
                    ui->FenEnvoiInvitation->hide();
                    ui->TxtOkInv->clear();
                    ui->TxtOkInvAccept->clear();
                    ui->FenInscription->show();
                    ui->FenInscription->setEnabled(false);
                    ui->ListeContact->setEnabled(true);

                    MainWindow::SupprInv();
                }
            }
        }

        if(TypesDonneesRecues == 2)
        {
            if(messageRecu.contains("ok", Qt::CaseSensitive))
            {
                /*qDebug() << "ok";
                if(messageRecu.contains(NomUserInv, Qt::CaseSensitive) || messageRecu.contains(ui->NomUserMultiplayer->text(), Qt::CaseSensitive))
                {*/
                    ui->TxtOkInvChargement->setText("Pret");
                    ui->TxtOkReceveurChargement->setText("Pret");
                    ui->BoutonJouerMultiplayerEnvoi->setEnabled(true);
                    ui->BoutonJouerMultiplayerRecev->setEnabled(true);

                    QSettings options("MultiplayerPartie.ini", QSettings::IniFormat);

                    options.setValue("utilisateur1", ui->NomUserMultiplayer->text());
                    options.setValue("score1", "100");
                    options.setValue("utilisateur2", NomUserInv);
                    options.setValue("score2", "100");

                    QMessageBox::critical(this,"Information","Sa commence !");
                //}
            }
            if(messageRecu.contains(NomUserMultiplayer, Qt::CaseSensitive))
            {
                QSettings options("MultiplayerPartie.ini", QSettings::IniFormat);

                options.setValue("score2", messageRecu);
            }
        }

        tailleMessage = 0;
}

void MainWindow::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur)
    {
        case QAbstractSocket::RemoteHostClosedError:
            ui->TxtStatutServeur->setText(tr("<em>ERREUR : La connexion a été coupée, cliquez sur le bouton 'actualiser le serveur'.</em>"));
            break;
        default:
        ui->TxtStatutServeur->setText(tr("<em>ERREUR : ") + socket->errorString() + tr(".</em>"));
    }
}

void MainWindow::error(QNetworkReply::NetworkError)
{
    qWarning("error retrieving RSS feed");
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
}

void MainWindow::ActuListeContact()
{
    if(db.open())
    {
        QString recherche_listecontact;
        recherche_listecontact = QString("SELECT friendwith FROM contact WHERE pseudmd='") + ui->NomUserMultiplayer->text() + QString("'");

        if (query_base->exec(recherche_listecontact))
        {
                while(query_base->next())
                           {

                               for(int x=0; x < 1; ++x)
                               {
                                       ui->ListeContact->addItem(query_base->record().value("friendwith").toString());

                                       EnsembleListeAmi += query_base->record().value("friendwith").toString() + QString(" ");
                               }
                           }
                EnsembleListeAmi += " ";
        }

    db.close();
    }
    else
    {
        QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
    }
}

void MainWindow::ActuInv()
{
    ui->BoutonJouerMultiplayerRecev->setEnabled(false);

    if(db.open())
    {
        QString recherche_listeinv;
        recherche_listeinv = QString("SELECT personnedemande FROM demande WHERE receveur='") + ui->NomUserMultiplayer->text() + QString("'");

        if (query_base->exec(recherche_listeinv))
        {
                while(query_base->next())
                           {

                               for(int x=0; x < 1; ++x)
                               {
                                   QString Question = "Voulez-vous faire une partie avec " + QString(query_base->record().value("personnedemande").toString());

                                   int QuestionInv = QMessageBox::question(this, "Information", Question, QMessageBox::Yes | QMessageBox::No);

                                   if(QuestionInv == QMessageBox::Yes)
                                   {
                                       QByteArray paquet;
                                       QDataStream out(&paquet, QIODevice::WriteOnly);

                                       // On prépare le paquet à envoyer
                                       QString messageAEnvoyer = ui->NomUserMultiplayer->text() + " oui";

                                       out << (quint16) 0;
                                       out << messageAEnvoyer;
                                       out.device()->seek(0);
                                       out << (quint16) (paquet.size() - sizeof(quint16));

                                       if(socket->write(paquet))
                                       {
                                           ui->FenInvitation->hide();
                                           ui->FenReceveurInv->show();

                                           TypesDonneesRecues = 2;
                                           NomUserMultiplayer = QString(query_base->record().value("personnedemande").toString());

                                           MainWindow::SupprInv();

                                           QMessageBox::critical(this,"Information","Envoyé !");
                                       }
                                   }
                                   else if(QuestionInv == QMessageBox::No)
                                   {
                                       QByteArray paquet;
                                       QDataStream out(&paquet, QIODevice::WriteOnly);

                                       // On prépare le paquet à envoyer
                                       QString messageAEnvoyer = QString(query_base->record().value("personnedemande").toString()) + " non";

                                       out << (quint16) 0;
                                       out << messageAEnvoyer;
                                       out.device()->seek(0);
                                       out << (quint16) (paquet.size() - sizeof(quint16));

                                       if(socket->write(paquet))
                                       {
                                           TypesDonneesRecues = 0;

                                           MainWindow::SupprInv();

                                           QMessageBox::critical(this,"Information","Envoyé !");
                                       }
                                   }

                               }
                           }
        }

    db.close();
    }
    else
    {
        QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
    }
}

void MainWindow::TimerFin()
{
    timer->stop();

    ui->FenEnvoiInvitation->hide();
    ui->TxtOkInv->clear();
    ui->TxtOkInvAccept->clear();
    ui->FenInvitation->show();
    ui->FenInscription->setEnabled(false);
    ui->ListeContact->setEnabled(true);

    QMessageBox::information(this,"Information",tr("Le contact n'est actuellement pas disponible"));

    if (db.open())
    {
                    QString requette_delinv;
                    requette_delinv = QString("DELETE FROM demande WHERE personnedemande='") + ui->NomUserMultiplayer->text() + QString("'");

                    if(query_base->exec(requette_delinv))
                    {

                    }
                    else
                    {
                        QMessageBox::critical(this,"Erreur",tr("Impossible d'éxecuter cette requette !"));
                    }

    db.close();
    }
    else
    {
        QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
    }
}

void MainWindow::SupprInv()
{
    if (db.open())
    {
                    QString requette_delinv;
                    requette_delinv = QString("DELETE FROM demande WHERE personnedemande='") + ui->NomUserMultiplayer->text() + QString("'");

                    if(query_base->exec(requette_delinv))
                    {

                    }
                    else
                    {
                        QMessageBox::critical(this,"Erreur",tr("Impossible d'éxecuter cette requette !"));
                    }

    db.close();
    }
    else
    {
        QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
    }
}

void MainWindow::LancerPendu()
{
    int NombreTimer;
    NombreTimer = 0;
    NombreTimer++;

    if(NombreTimer == 2)
    {
        timer2->stop();
    }

    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On prépare le paquet à envoyer
    QString messageAEnvoyer = "ok";

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    if(socket->write(paquet))
    {

    }
}

void MainWindow::on_ListeContact_clicked()
{
    ui->FenInvitation->setEnabled(true);
    ui->TxtInvitation->setText("Bonjour " + ui->ListeContact->currentItem()->text() + ", je souhaiterais jouer avec vous.");
}

void MainWindow::on_BoutonInviter_clicked()
{
    NomUserInv = ui->ListeContact->currentItem()->text();
    NomUserMultiplayer = ui->ListeContact->currentItem()->text();
    TypesDonneesRecues = 1;

    ui->ListeContact->setEnabled(false);
    ui->FenInvitation->setEnabled(false);
    ui->BoutonJouerMultiplayerEnvoi->setEnabled(false);
    ui->FenInvitation->hide();
    ui->FenEnvoiInvitation->show();
    ui->TxtOkInv->setText("...");

    if (db.open())
    {
            QString requette_addinv;
            requette_addinv = QString("INSERT INTO demande VALUE ('','") + ui->NomUserMultiplayer->text() + QString("', '") + ui->ListeContact->currentItem()->text() + QString("')");

            if(query_base->exec(requette_addinv))
            {
                QByteArray paquet;
                QDataStream out(&paquet, QIODevice::WriteOnly);

                // On prépare le paquet à envoyer
                QString messageAEnvoyer = "demande";

                out << (quint16) 0;
                out << messageAEnvoyer;
                out.device()->seek(0);
                out << (quint16) (paquet.size() - sizeof(quint16));

                if(socket->write(paquet))
                {
                    timer->start(60000);

                    ui->TxtOkInv->setText("Ok");
                    ui->TxtOkInvAccept->setText("...");
                }
            }
            else
            {
                QMessageBox::critical(this,"Erreur",tr("Impossible d'effectuer cette requette !"));
            }

    db.close();
    }
}

void MainWindow::on_BoutonDeconnexion_clicked()
{
    if(db.open())
    {
                QString requette_deco;
                requette_deco = QString("UPDATE user SET etat='disco' WHERE pseudo='") + ui->txt_pseudo->text() + QString("'");

                if (query_base->exec(requette_deco))
                {
                    ui->FenInfoMulti->hide();
                    ui->FenEnvoiInvitation->hide();
                    ui->TxtOkInv->clear();
                    ui->TxtOkInvAccept->clear();
                    ui->TxtOkInvChargement->clear();
                    ui->FenReceveurInv->hide();
                    ui->TxtOkInvChargement->clear();
                    ui->TxtOkReceveurChargement->clear();
                    ui->FenInvitation->show();
                    ui->FenMultiplayer->show();
                    ui->BoutonRetour->show();
                    ui->pseudo->setFocus();
                    ui->ListeContact->setEnabled(true);
                    ui->TxtInvitation->clear();
                }

    db.close();
    }
    else
    {
        QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings options("config.ini", QSettings::IniFormat);

    if(options.value("modehorsligne") == true)
    {

    }
    else
    {
        if(db.open())
        {
                    QString requette_deco;
                    requette_deco = QString("UPDATE user SET etat='disco' WHERE pseudo='") + ui->NomUserMultiplayer->text() + QString("'");

                    if (query_base->exec(requette_deco))
                    {

                    }
        db.close();
        }
        else
        {
            QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
        }
    }

    if(TypesFermeture == 1)
    {
        int quitter = QMessageBox::question(this, "Information",tr("Etes-vous sûr de vouloir quitter le pendu en cours ?"), QMessageBox::Yes | QMessageBox::No);

        if(quitter == QMessageBox::Yes)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }

    }
    else if(TypesFermeture == 2)
    {
        int quitter = QMessageBox::question(this, "Information",tr("Etes-vous sûr de vouloir quitter le mode multijoueur ?"), QMessageBox::Yes | QMessageBox::No);

        if(quitter == QMessageBox::Yes)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::on_BoutonInscription_clicked()
{
    ui->BoutonInscription->hide();
    ui->FenInscription->show();
}

void MainWindow::on_BoutonValiderInscription_clicked()
{
    QString age = "0";

    if(ui->Ageinscri->text() == age)
    {
        QMessageBox::critical(this, "Erreur",tr("Vous devez renseigner votre age !"));
    }
    else

    if (ui->rules->isChecked() != false)//verif que la checkbox soit cocher !
       {

           int reponse = QMessageBox::question(this, "Information",tr("Vous avez accepté les règles. Voulez vous les consulter ?"), QMessageBox::Yes | QMessageBox::No);

           if (reponse == QMessageBox::Yes)
               {
                   QProcess::execute("cmd /c start http://loquii.alwaysdata.net");
               }
           else if (reponse == QMessageBox::No)
               {

               }

           if (ui->mdp_inscri->text() == "" || ui->mdp_comfirm->text() == "") // verif que les champs des mdp ne sont pas vide
           {
               QMessageBox::critical(this, "Erreur",tr("Vous n'avez pas entré de mot de passe !"));
           }
           else
           {

                   if (ui->mdp_comfirm->text() == ui->mdp_inscri->text()) //verification des mots de passe
                       {
                               if (ui->pseudo_inscri->text() == "")
                                   {
                                       QMessageBox::critical(this, "Erreur",tr("Vous devez renseigner un pseudo !"));
                                   }
                               else
                                   {

                                           QRegExp mailExp ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$"); //expression reguliere pour verifier l'adresse a une forme valide
                                           QString EntryText = ui->entrEmail->text ();
                                           if (EntryText.contains (mailExp))//verification de l'adresse email !
                                               {

                                                   if (db.open())
                                                           {
                                                       QString requette_pseudoexist;
                                                       requette_pseudoexist = QString("SELECT COUNT(*) AS pseudo_exist FROM user WHERE pseudo='") + ui->pseudo_inscri->text() + QString("'");

                                                       if(query_base->exec(requette_pseudoexist))
                                                       {
                                                           while(query_base->next())
                                                                      {
                                                                          for(int x=0; x < query_base->record().count(); ++x)
                                                                          {
                                                                               entier = query_base->record().value("pseudo_exist").toInt();
                                                                          }
                                                                       }
                                                                               entier ++;
                                                                               //if de test du carractere recuperer !

                                                                               if (entier == 2)
                                                                               {
                                                                                   QMessageBox::warning(this, "Attention !",tr("Le pseudo que vous avez entré est deja utilisé !"));
                                                                               }
                                                                               else
                                                                               {
                                                                                   QString mdp = ui->mdp_inscri->text();
                                                                                   QByteArray ba = QCryptographicHash::hash(mdp.toUtf8(), QCryptographicHash::Sha1); // on la hache
                                                                                   QString mdp_hache = ba.toHex(); // on convertit le hash en QString

                                                                                   QString requetter_nouvuser;
                                                                                   requetter_nouvuser = QString("INSERT INTO user VALUE ('','") + ui->entrEmail->text() + QString("','") + ui->pseudo_inscri->text() + QString("','") + mdp_hache + QString("','','") + ui->Ageinscri->text() + QString("','") + ui->choix_pay->currentText() + QString("','disco','','','1')");

                                                                                   if (query_base->exec(requetter_nouvuser))
                                                                                   {
                                                                                       QMessageBox::information(this, "Information",tr("L'inscription est terminée. \n Pour vous connecter, cliquez sur le bouton retour"));

                                                                                       ui->pseudo_inscri->clear();
                                                                                       ui->mdp_inscri->clear();
                                                                                       ui->mdp_comfirm->clear();
                                                                                       ui->choix_pay->setCurrentIndex(0);
                                                                                       ui->entrEmail->clear();
                                                                                       ui->Ageinscri->setValue(0);
                                                                                       ui->rules->setChecked(false);
                                                                                       ui->FenInscription->hide();
                                                                                       ui->BoutonInscription->show();
                                                                                   }
                                                                                   else
                                                                                   {
                                                                                       QMessageBox::critical(this,"Erreur",tr(" Impossible de vous enregistrer dans la base de donnee ! \n verrifiez votre connection Internet ou \n reessayez plus tard ,  Nous somme peut-etre en maintenance"));
                                                                                   }
                                                                               }
                                                       }
                                                               else
                                                               {
                                                                   QMessageBox::critical(this, "Erreur",tr(" Impossible de se connecter a la base de Donnée\nVerrifiez votre connexion internet"));
                                                               }
                                                   db.close();
                                                   }
                                                   else
                                                   {
                                                       QMessageBox::critical(this, "Erreur",tr("Impossible de se connecter a la base de Donnée\nVerrifiez votre connexion internet"));
                                                   }
                                               }
                                            else
                                               {
                                                   QMessageBox::critical (this, "Erreur", EntryText + tr(" n'est pas une adresse mail valide !"));
                                               }
                                     }
                       }
                       else
                       {
                           QMessageBox::critical(this, "Erreur",tr("Les mots de passe ne sont pas identique !"));
                       }
           }

       }
       else
       {
           QMessageBox::critical(this, "Erreur",tr("vous devez accepter les regles !"));
       }
}

void MainWindow::on_BoutonOk_clicked()
{
    ui->FenResultat->hide();

    ui->BoutonRejouer->setEnabled(true);
}

void MainWindow::on_BoutonOptions_clicked()
{
    ui->FenPendu->hide();
    ui->FenMenu->hide();
    ui->GroupBoxScore->hide();
    ui->NomUserPendu->hide();
    ui->BoutonQuitter->hide();
    ui->BoutonRejouer->hide();
    ui->FenScore->hide();
    ui->FenOptions->show();
    ui->BoutonRetour->show();

    QSettings options("config.ini", QSettings::IniFormat);

    if(QString(options.value("niveau").toString()) == "facile")
    {
        ui->NiveauFacile->setChecked(true);
    }
    else if(QString(options.value("niveau").toString()) == "moyen")
    {
        ui->NiveauMoyen->setChecked(true);
    }
    else if(QString(options.value("niveau").toString()) == "difficile")
    {
        ui->NiveauDifficile->setChecked(true);
    }

    if(options.value("indice") == true)
    {
        ui->CheckActiverIndice->setChecked(true);
    }
    else
    {
        ui->CheckActiverIndice->setChecked(false);
    }
}

void MainWindow::on_CheckActiverIndice_clicked()
{
    QSettings options("config.ini", QSettings::IniFormat);

    if(ui->CheckActiverIndice->isChecked() == true)
    {
        options.setValue("indice", true);
    }
    else
    {
        options.setValue("indice", false);
    }
}

void MainWindow::on_BoutonChangerPolice_clicked()
{
    bool ok = false;
    QFont police;
    police = QFontDialog::getFont(&ok, police, this);

        if(ok)
        {
            QSettings options("config.ini", QSettings::IniFormat);

            options.setValue("police", police);

            this->setFont(police);
            ui->NomPolice->setText(QString(police.toString()));
        }
}

void MainWindow::on_BoutonChangerDeFond_clicked()
{
    CheminImg = QFileDialog::getOpenFileName(this,tr("Ajouter l'image"), QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    MainWindow::CopierColler();
}

void MainWindow::CopierColler()
{
    QFile ImageFond(CheminImg);
    ImageFond.copy("images/img.png");
}

void MainWindow::on_NiveauFacile_clicked()
{
    QSettings options("config.ini", QSettings::IniFormat);

    options.setValue("niveau", "facile");
}

void MainWindow::on_NiveauMoyen_clicked()
{
    QSettings options("config.ini", QSettings::IniFormat);

    options.setValue("niveau", "moyen");
}

void MainWindow::on_NiveauDifficile_clicked()
{
    QSettings options("config.ini", QSettings::IniFormat);

    options.setValue("niveau", "difficile");
}

void MainWindow::on_BoutonScore_clicked()
{
    ui->FenPendu->hide();
    ui->FenMenu->hide();
    ui->GroupBoxScore->hide();
    ui->NomUserPendu->hide();
    ui->BoutonQuitter->hide();
    ui->BoutonRejouer->hide();
    ui->FenScore->show();
    ui->BoutonRetour->show();

    QSettings options("config.ini", QSettings::IniFormat);

    if(options.value("modehorsligne") == true)
    {
        std::string NomFichierScore = ui->NomUser->text().toStdString() + ".sre";
        ifstream FichierScore(NomFichierScore.c_str(), ios::in);

        if(FichierScore)
        {
            string ligne;

            while(getline(FichierScore, ligne))
            {
                ui->InfoScore->append(ligne.c_str());
            }
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de lire le fichier ( Fichier des scores ) !");
        }
    }
    else
    {
        if(db.open())
        {
            QString html_text;

            QString requette_actunot;
            requette_actunot = QString("SELECT * from score WHERE user='") + ui->NomUser->text() + QString("'");

            if (query_base->exec(requette_actunot))
            {
                while(query_base->next())
                {
                    for(int x=0; x < 1; ++x)
                    {
                        QDateTime DateTimeScore;
                        uint sec = query_base->record().value("date").toUInt();

                        html_text = QString("<div style=\"width : 250px;font-size: 0.8em; position:relative;\"><fieldset><span align=\"left\"><strong>") + query_base->record().value("score").toString() + QString("</strong>; le ") + DateTimeScore.fromTime_t(sec).toString() + QString("</span></fieldset></div><br/> ---- ");
                        ui->InfoScore->append(html_text);
                    }

                }


            }

        db.close();
        }
        else
        {
            QMessageBox::information(this, "Erreur",tr("Connexion impossible à la base de données."));
        }
    }
}

void MainWindow::on_BoutonRetour_clicked()
{
    ui->BoutonRetour->hide();
    ui->FenScore->hide();
    ui->FenOptions->hide();
    ui->FenMultiplayer->hide();
    ui->FenMenu->show();
    ui->GroupBoxScore->show();
    ui->pseudo->clear();
    ui->mdp->clear();

    TypesFermeture = 0;
}

void MainWindow::on_BoutonQuitter_clicked()
{
    if(ui->BoutonRejouer->isEnabled() == false)
    {
        int quitter = QMessageBox::question(this, "Information",tr("Etes-vous sûr de vouloir quitter le pendu en cours ?"), QMessageBox::Yes | QMessageBox::No);

        if(quitter == QMessageBox::Yes)
        {
            ui->Tentative->clear();
            ui->LettresDonnee->clear();
            ui->Score->clear();
            ui->NomImg->setText("0");

            ui->FenPendu->hide();
            ui->BoutonQuitter->hide();
            ui->BoutonRejouer->hide();
            ui->NomUserPendu->hide();
            ui->TxtNiveau->hide();
            ui->TempsRestant->hide();
            ui->FenMenu->show();
            ui->GroupBoxScore->show();

            TypesFermeture = 0;
        }
        else
        {

        }

    }
    else
    {
        ui->FenPendu->hide();
        ui->BoutonQuitter->hide();
        ui->BoutonRejouer->hide();
        ui->NomUserPendu->hide();
        ui->TxtNiveau->hide();
        ui->TempsRestant->hide();
        ui->FenMenu->show();
        ui->GroupBoxScore->show();

        TypesFermeture = 0;
    }
}

void MainWindow::Depart()
{
    QString MotSecret;

    int *LettreTrouvee = NULL; // Un tableau de boolÃ©ens. Chaque case correspond Ã  une Lettre du Mot secret. 0 = Lettre non trouvÃ©e, 1 = Lettre trouvÃ©
    long i = 0; // Une petite variable pour parcourir les tableaux
    long tailleMot = 0;

    ui->LettresDonnee->clear();
    ui->Tentative->setText("0");
    ui->NomImg->setText("0");

    score = 100;
    Indice = 0;
    TypesFermeture = 1;

    ui->Score->setText(QString::number(score));

    ui->png_1->hide();
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

    ui->touche->setEnabled(true);
    ui->touche_2->setEnabled(true);
    ui->touche_3->setEnabled(true);
    ui->touche_4->setEnabled(true);
    ui->touche_5->setEnabled(true);
    ui->touche_6->setEnabled(true);
    ui->touche_7->setEnabled(true);
    ui->touche_8->setEnabled(true);
    ui->touche_9->setEnabled(true);
    ui->touche_10->setEnabled(true);
    ui->touche_11->setEnabled(true);
    ui->touche_12->setEnabled(true);
    ui->touche_13->setEnabled(true);
    ui->touche_14->setEnabled(true);
    ui->touche_15->setEnabled(true);
    ui->touche_16->setEnabled(true);
    ui->touche_17->setEnabled(true);
    ui->touche_18->setEnabled(true);
    ui->touche_19->setEnabled(true);
    ui->touche_20->setEnabled(true);
    ui->touche_21->setEnabled(true);
    ui->touche_22->setEnabled(true);
    ui->touche_23->setEnabled(true);
    ui->touche_24->setEnabled(true);
    ui->ToucheY->setEnabled(true);
    ui->ToucheZ->setEnabled(true);

    QSettings options("config.ini", QSettings::IniFormat);

    if(options.value("indice") == true)
    {
        ui->BoutonIndice->setEnabled(true);
    }
    else
    {
        ui->BoutonIndice->setEnabled(false);
    }

    options.setValue("utilisateur", ui->NomUser->text());

    ui->TxtNiveau->setText("Niveau " + QString(options.value("niveau").toString()));

    ui->FenMenu->hide();
    ui->FenResultat->hide();
    ui->FenScore->hide();
    ui->GroupBoxScore->hide();
    ui->TxtSansFautes->hide();
    ui->TxtNiveau->show();
    ui->NomUserPendu->show();
    ui->BoutonQuitter->show();
    ui->BoutonRejouer->show();
    ui->TempsRestant->show();
    ui->FenPendu->show();

    ui->BoutonRejouer->setEnabled(false);
    ui->FenPendu->setEnabled(true);

    ui->NomUserPendu->setText(ui->NomUser->text());

    MotSecret = MainWindow::MotAleatoire();

    if (MotSecret.contains("ERROR", Qt::CaseSensitive))
    {
        ui->FenPendu->setEnabled(false);
        ui->BoutonRejouer->hide();
        ui->GroupBoxScore->hide();
        ui->FenMenu->hide();
        ui->FenResultat->hide();
        ui->FenScore->hide();
        ui->BoutonQuitter->show();

        QMessageBox::critical(this,"Erreur","Veuillez réinstaller le jeu");
    }
    else
    {
    ui->MotPioche->setText(MotSecret);
    MotPioche = MotSecret;

    tailleMot = MotSecret.size();
    LettreTrouvee = new int[tailleMot]; // On alloue dynamiquement le tableau LettreTrouvee (dont on ne connaissait pas la taille au dÃ©part)
        if (LettreTrouvee == NULL)
            exit(0);

     QString MotEtoile;
     for (i = 0 ; i < tailleMot ; i++)
     {
          LettreTrouvee[i] = 0;
          MotEtoile += "*";

     }
     ui->MotATrouver->setText(MotEtoile);
    }
}

QString MainWindow::MotAleatoire()
{
    int MAX = 0;
    char caractere = 0;

    QSettings options("config.ini", QSettings::IniFormat);

    if(QString(options.value("niveau").toString()) == "facile")
    {
        NomFichierDico = "Dictionnaire/DicoFacile.dico";
    }
    else if(QString(options.value("niveau").toString()) == "moyen")
    {
        NomFichierDico = "Dictionnaire/DicoMoyen.dico";
    }
    else if(QString(options.value("niveau").toString()) == "difficile")
    {
        NomFichierDico = "Dictionnaire/DicoDifficile.dico";
    }

    QFile FichierDico(NomFichierDico);

    if (!FichierDico.open(QIODevice::ReadOnly))
        return ("ERROR");
    QTextStream fichier(&FichierDico);

    // Compte du nombre de Mots
    while (!fichier.atEnd())
    {
        fichier >> caractere;

        if (caractere == '\n')
            MAX++;
    }

    fichier.seek(0);

    // Definition du nombre alÃ©atoire
    // et positionnement dans le fichier
    int ligneAleat = rand() % MAX;
    int t = 0;

    while (t != ligneAleat)
    {
        fichier >> caractere;
        if (caractere == '\n')
            t++;
    }

    // Retour du Mot selectionnÃ©
    QString Mot;
    fichier >> Mot;

    MotMultiplayer = Mot;

    return Mot;
}

void MainWindow::RechercheLettre(QString Lettre)
{
        int i = 0;
        int bonneLettre = 0;

        QString MotSecret;
        MotSecret = ui->MotPioche->text();
        QString MotEtoile;
        MotEtoile = ui->MotATrouver->text();
        QString Mot;

        QString LettreAddListe = " " + Lettre;
        QString EnsembleLettre = ui->LettresDonnee->text();
        EnsembleLettre += LettreAddListe;
        ui->LettresDonnee->setText(EnsembleLettre);

        int Tentative = ui->Tentative->text().toInt();
        Tentative++;
        ui->Tentative->setText(QString::number(Tentative));

        // On parcourt MotSecret pour vÃ©rifier si la Lettre proposÃ©e y est
        for (i = 0 ; MotSecret[i] != '\0' ; i++)
        {
            Mot = MotSecret[i];
        // QMessageBox::critical(this, "fff", Mot);
            if (Mot == Lettre) // Si la Lettre y est
            {
                 bonneLettre = 1; // On mÃ©morise que c'Ã©tait une bonne Lettre
                 // LettreTrouvee[i] = 1; // On met Ã  1 le case du tableau de boolÃ©ens correspondant Ã  la Lettre actuelle
                 MotEtoile.replace(i,1, Lettre);
            }

            ui->MotATrouver->setText(MotEtoile);
        }

        if(bonneLettre == 1)
        {
            score = score + 80;

            ui->Score->setText(QString::number(score));
        }
        else
        {
            score = score - 20;

            ui->Score->setText(QString::number(score));

            MainWindow::AfficherPendu();
        }

    MainWindow::Gagner(ui->MotATrouver->text());
}

void MainWindow::on_BoutonIndice_clicked()
{
    Indice = 1;
    ui->BoutonIndice->setEnabled(false);

    if(ui->MotPioche->text().contains("a",Qt::CaseSensitive))
    {
        MainWindow::on_touche_clicked();
    }
    else if(ui->MotPioche->text().contains("b",Qt::CaseSensitive))
    {
        MainWindow::on_touche_2_clicked();
    }
    else if(ui->MotPioche->text().contains("c",Qt::CaseSensitive))
    {
        MainWindow::on_touche_3_clicked();
    }
    else if(ui->MotPioche->text().contains("d",Qt::CaseSensitive))
    {
        MainWindow::on_touche_4_clicked();
    }
    else if(ui->MotPioche->text().contains("e",Qt::CaseSensitive))
    {
        MainWindow::on_touche_5_clicked();
    }
    else if(ui->MotPioche->text().contains("f",Qt::CaseSensitive))
    {
        MainWindow::on_touche_6_clicked();
    }
    else if(ui->MotPioche->text().contains("g",Qt::CaseSensitive))
    {
        MainWindow::on_touche_7_clicked();
    }
    else if(ui->MotPioche->text().contains("h",Qt::CaseSensitive))
    {
        MainWindow::on_touche_8_clicked();
    }
    else if(ui->MotPioche->text().contains("i",Qt::CaseSensitive))
    {
        MainWindow::on_touche_9_clicked();
    }
    else if(ui->MotPioche->text().contains("j",Qt::CaseSensitive))
    {
        MainWindow::on_touche_10_clicked();
    }
    else if(ui->MotPioche->text().contains("k",Qt::CaseSensitive))
    {
        MainWindow::on_touche_11_clicked();
    }
    else if(ui->MotPioche->text().contains("l",Qt::CaseSensitive))
    {
        MainWindow::on_touche_12_clicked();
    }
    else if(ui->MotPioche->text().contains("m",Qt::CaseSensitive))
    {
        MainWindow::on_touche_13_clicked();
    }
    else if(ui->MotPioche->text().contains("n",Qt::CaseSensitive))
    {
        MainWindow::on_touche_14_clicked();
    }
    else if(ui->MotPioche->text().contains("o",Qt::CaseSensitive))
    {
        MainWindow::on_touche_15_clicked();
    }
    else if(ui->MotPioche->text().contains("p",Qt::CaseSensitive))
    {
        MainWindow::on_touche_16_clicked();
    }
    else if(ui->MotPioche->text().contains("q",Qt::CaseSensitive))
    {
        MainWindow::on_touche_17_clicked();
    }
    else if(ui->MotPioche->text().contains("r",Qt::CaseSensitive))
    {
        MainWindow::on_touche_18_clicked();
    }
    else if(ui->MotPioche->text().contains("s",Qt::CaseSensitive))
    {
        MainWindow::on_touche_19_clicked();
    }
    else if(ui->MotPioche->text().contains("t",Qt::CaseSensitive))
    {
        MainWindow::on_touche_20_clicked();
    }
    else if(ui->MotPioche->text().contains("u",Qt::CaseSensitive))
    {
        MainWindow::on_touche_21_clicked();
    }
    else if(ui->MotPioche->text().contains("v",Qt::CaseSensitive))
    {
        MainWindow::on_touche_22_clicked();
    }
    else if(ui->MotPioche->text().contains("w",Qt::CaseSensitive))
    {
        MainWindow::on_touche_23_clicked();
    }
    else if(ui->MotPioche->text().contains("x",Qt::CaseSensitive))
    {
        MainWindow::on_touche_24_clicked();
    }
    else if(ui->MotPioche->text().contains("y",Qt::CaseSensitive))
    {
        MainWindow::on_ToucheY_clicked();
    }
    else if(ui->MotPioche->text().contains("z",Qt::CaseSensitive))
    {
        MainWindow::on_ToucheZ_clicked();
    }
}

void MainWindow::Gagner(QString MotATrouver)
{
    if (MotATrouver.contains("*", Qt::CaseSensitive))
    {

    }
    else
    {
        ui->FenPendu->setEnabled(false);

        QSettings options("config.ini", QSettings::IniFormat);

        if(options.value("modehorsligne") == true)
        {
            std::string NomFichierScore = ui->NomUser->text().toStdString() + ".sre";
            ofstream FichierScore(NomFichierScore.c_str(), ios::out | ios::trunc);

            if(FichierScore)
            {
                QTime TimeScore;

                std::string time = "<em>" + TimeScore.currentTime().toString().toStdString() + " ;</em>";
                std::string nom = ui->NomUser->text().toStdString();
                std::string score_fichier = QString::number(score).toStdString();

                QDate DateScore;

                std::string date_aff = "<strong>" + DateScore.currentDate().toString().toStdString() + "</strong>";

                FichierScore << date_aff << endl;

                FichierScore << time << ' ' << nom << " à gagné : " << score_fichier << endl;

                FichierScore.close();
            }
            else
            {
                QMessageBox::critical(this,"Erreur","Impossible de lire le fichier ( Fichier des scores ) !");
            }
        }
        else
        {
            if (db.open())
            {
                QDateTime DateTimeScore;

                QString requette_addscore;
                requette_addscore = QString("INSERT INTO score VALUE ('','") + ui->NomUser->text() + QString("', '") + QString::number(score) + QString("', '") + QString::number(DateTimeScore.currentDateTime().toTime_t()) + QString("')");

                    if(query_base->exec(requette_addscore))
                    {

                    }

            db.close();
            }
        }

        if(Indice == 1)
        {
            score = score + 20;

            ui->Score->setText(QString::number(score));
            ui->TxtSansIndice->show();
        }

        if(ui->NomImg->text().toInt() == 0)
        {
            score = score + 20;

            ui->Score->setText(QString::number(score));
            ui->TxtSansFautes->show();
        }

        if(options.value("dernierscore").toString() == "")
        {
            ui->DernierScore->setText("aucun");
        }
        else
        {
            ui->DernierScore->setText(QString(options.value("dernierscore").toString()));
        }

        options.setValue("dernierscore", QString::number(score));

        int NombrePartie = options.value("nombrepartie").toInt() + 1;

        options.setValue("nombrepartie", QString::number(NombrePartie));


        ui->NombreParties->setText(QString(options.value("nombrepartie").toString()));
        ui->FenPendu->setEnabled(false);
        ui->FenResultat->show();
        ui->Resultat->setText("Vous avez gagné !");
        ui->TxtMotPerdu->hide();
        ui->ScoreResultat->setText(QString::number(score));
    }
}

void MainWindow::AfficherPendu()
{
    int ActuErreur = ui->NomImg->text().toInt();
    ActuErreur++;

    ui->NomImg->setText(QString::number(ActuErreur));

    if(ActuErreur == 1)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_1->show();
    }
    else if(ActuErreur == 2)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_2->show();
    }
    else if(ActuErreur == 3)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_3->show();
    }
    else if(ActuErreur == 4)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_4->show();
    }
    else if(ActuErreur == 5)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_5->show();
    }
    else if(ActuErreur == 6)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_6->show();
    }
    else if(ActuErreur == 7)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_7->show();
    }
    else if(ActuErreur == 8)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_8->show();
    }
    else if(ActuErreur == 9)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_9->show();
    }
    else if(ActuErreur == 10)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_10->show();
    }
    else if(ActuErreur == 11)
    {
        score = score - 60;

        ui->Score->setText(QString::number(score));

        ui->png_11->show();

        QSettings options("config.ini", QSettings::IniFormat);

        if(options.value("modehorsligne") == true)
        {
            std::string NomFichierScore = ui->NomUser->text().toStdString() + ".sre";
            ofstream FichierScore(NomFichierScore.c_str(), ios::out | ios::trunc);

            if(FichierScore)
            {
                QTime TimeScore;

                std::string time = "<em>" + TimeScore.currentTime().toString().toStdString() + " ;</em>";
                std::string nom = ui->NomUser->text().toStdString();
                std::string score_fichier = QString::number(score).toStdString();

                QDate DateScore;

                std::string date_aff = "<strong>" + DateScore.currentDate().toString().toStdString() + "</strong>";

                FichierScore << date_aff << endl;

                FichierScore << time << ' ' << nom << " à gagné : " << score_fichier << endl;

                FichierScore.close();
            }
            else
            {
                QMessageBox::critical(this,"Erreur","Impossible de lire le fichier ( Fichier des scores ) !");
            }
        }
        else
        {
            if (db.open())
            {
                QDateTime DateTimeScore;

                QString requette_addscore;
                requette_addscore = QString("INSERT INTO score VALUE ('','") + ui->NomUser->text() + QString("', '") + QString::number(score) + QString("', '") + QString::number(DateTimeScore.currentDateTime().toTime_t()) + QString("')");

                    if(query_base->exec(requette_addscore))
                    {

                    }

            db.close();
            }
        }

        if(options.value("dernierscore").toString() == "")
        {
            ui->DernierScore->setText("aucun");
        }
        else
        {
            ui->DernierScore->setText(QString(options.value("dernierscore").toString()));
        }

        options.setValue("dernierscore", QString::number(score));

        int NombrePartie = options.value("nombrepartie").toInt() + 1;

        options.setValue("nombrepartie", QString::number(NombrePartie));

        ui->NombreParties->setText(QString(options.value("nombrepartie").toString()));

        ui->FenPendu->setEnabled(false);
        ui->FenResultat->show();
        ui->Resultat->setText("Vous avez perdu !");
        ui->TxtMotPerdu->show();
        ui->TxtMotPerdu->setText("Le Mot était : " + MotPioche);
        ui->ScoreResultat->setText(QString::number(score));
    }
}

void MainWindow::on_touche_clicked()
{
    ui->touche->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche->text());
}

void MainWindow::on_touche_2_clicked()
{
    ui->touche_2->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_2->text());
}

void MainWindow::on_touche_3_clicked()
{
    ui->touche_3->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_3->text());
}

void MainWindow::on_touche_4_clicked()
{
    ui->touche_4->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_4->text());
}

void MainWindow::on_touche_5_clicked()
{
    ui->touche_5->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_5->text());
}

void MainWindow::on_touche_6_clicked()
{
    ui->touche_6->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_6->text());
}

void MainWindow::on_touche_7_clicked()
{
    ui->touche_7->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_7->text());
}

void MainWindow::on_touche_8_clicked()
{
    ui->touche_8->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_8->text());
}

void MainWindow::on_touche_9_clicked()
{
    ui->touche_9->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_9->text());
}

void MainWindow::on_touche_10_clicked()
{
    ui->touche_10->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_10->text());
}

void MainWindow::on_touche_11_clicked()
{
    ui->touche_11->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_11->text());
}

void MainWindow::on_touche_12_clicked()
{
    ui->touche_12->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_12->text());
}

void MainWindow::on_touche_13_clicked()
{
    ui->touche_13->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_13->text());
}

void MainWindow::on_touche_14_clicked()
{
    ui->touche_14->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_14->text());
}

void MainWindow::on_touche_15_clicked()
{
    ui->touche_15->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_15->text());
}

void MainWindow::on_touche_16_clicked()
{
    ui->touche_16->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_16->text());
}

void MainWindow::on_touche_17_clicked()
{
    ui->touche_17->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_17->text());
}

void MainWindow::on_touche_18_clicked()
{
    ui->touche_18->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_18->text());
}

void MainWindow::on_touche_19_clicked()
{
    ui->touche_19->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_19->text());
}

void MainWindow::on_touche_20_clicked()
{
    ui->touche_20->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_20->text());
}

void MainWindow::on_touche_21_clicked()
{
    ui->touche_21->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_21->text());
}


void MainWindow::on_touche_22_clicked()
{
    ui->touche_22->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_22->text());
}

void MainWindow::on_touche_23_clicked()
{
    ui->touche_23->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_23->text());
}

void MainWindow::on_touche_24_clicked()
{
    ui->touche_24->setEnabled(false);
    MainWindow::RechercheLettre(ui->touche_24->text());
}

void MainWindow::on_ToucheY_clicked()
{
    ui->ToucheY->setEnabled(false);
    MainWindow::RechercheLettre(ui->ToucheY->text());
}

void MainWindow::on_ToucheZ_clicked()
{
    ui->ToucheZ->setEnabled(false);
    MainWindow::RechercheLettre(ui->ToucheZ->text());
}

int MainWindow::nombreAleatoire(int nombreMax)
{
        srand(time(NULL));
        return (rand() % nombreMax);
}

MainWindow::~MainWindow()
{
    delete ui;
}
