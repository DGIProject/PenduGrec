#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void on_touche_9_clicked();
    void base_start();
    QString TrouverMot();
    QString TrouverTraduct(int ligne);
    int nombreAleatoire(int nombreMax);
    int gagne(QString mot_etoile);
    int rechercheLettre(QString lettre);
    void on_actionNouveau_Mot_triggered();
    void on_actionAfficher_le_dictionaire_triggered();
    void on_actionQuitter_triggered();
    void AfficherPendu();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
