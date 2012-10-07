#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QtSql>
#include <QTcpSocket>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_touche_clicked();
    void on_touche_2_clicked();
    void on_touche_3_clicked();
    void on_touche_4_clicked();
    void on_touche_5_clicked();
    void on_touche_6_clicked();
    void on_touche_7_clicked();
    void on_touche_8_clicked();
    void on_touche_9_clicked();
    void on_touche_10_clicked();
    void on_touche_11_clicked();
    void on_touche_12_clicked();
    void on_touche_13_clicked();
    void on_touche_14_clicked();
    void on_touche_15_clicked();
    void on_touche_16_clicked();
    void on_touche_17_clicked();
    void on_touche_18_clicked();
    void on_touche_19_clicked();
    void on_touche_20_clicked();
    void on_touche_21_clicked();
    void on_touche_22_clicked();
    void on_touche_23_clicked();
    void on_touche_24_clicked();
    void on_ToucheY_clicked();
    void on_ToucheZ_clicked();
    int nombreAleatoire(int nombreMax);

    void Depart();
    void on_BoutonIndice_clicked();
    void RechercheLettre(QString Lettre);
    void Gagner(QString MotATrouver);
    void AfficherPendu();
    QString MotAleatoire();
    void on_BoutonJouer_clicked();
    void on_BoutonRejouer_clicked();
    void on_BoutonOk_clicked();
    void on_BoutonOptions_clicked();
    void on_CheckActiverIndice_clicked();
    void on_BoutonScore_clicked();
    void on_BoutonRetour_clicked();
    void on_BoutonMultiplayer_clicked();
    void on_BoutonConnection_clicked();
    void on_BoutonActuServ_clicked();
    void connecte();
    void deconnecte();
    void donneesRecues();
    void erreurSocket(QAbstractSocket::SocketError erreur);
    void error(QNetworkReply::NetworkError);
    void ActuListeContact();
    void ActuInv();
    void TimerFin();
    void SupprInv();
    void LancerPendu();
    void on_ListeContact_clicked();
    void on_BoutonInviter_clicked();
    void on_BoutonDeconnexion_clicked();
    void on_BoutonInscription_clicked();
    void on_BoutonValiderInscription_clicked();
    void on_BoutonQuitter_clicked();
    void on_BoutonChangerPolice_clicked();
    void on_BoutonChangerDeFond_clicked();
    void CopierColler();
    void on_NiveauFacile_clicked();
    void on_NiveauMoyen_clicked();
    void on_NiveauDifficile_clicked();

private:

    Ui::MainWindow *ui;

    int score;
    int entier;
    int TypesDonneesRecues;
    int Indice;
    int TypesFermeture;

    QString NomFichierDico;
    QString CheminImg;
    QString MotPioche;
    QString EnsembleListeAmi;
    QString NomUserInv;
    QString NomUserMultiplayer;
    QTimer *timer;
    QTimer *timer2;
    QString MotMultiplayer;

public :
    QTcpSocket *socket;
    quint16 tailleMessage;
    QNetworkReply *currentReply;
    QSqlDatabase db;
    QSqlQuery* query_base;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
