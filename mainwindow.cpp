#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSoundEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->volumeValue->setText(QString::number(ui->volumeDial->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pianoKey(int key)
{
    QList<QMediaContent> filelist;
    filelist << QUrl::fromLocalFile("..\\cPiano\\sounds\\C5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\C5_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\D5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\D5_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\E5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\F5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\F5_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\G5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\G5_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\A5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\A5_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\B5.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\C6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\C6_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\D6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\D6_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\E6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\F6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\F6_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\G6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\G6_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\A6.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\A6_Sharp.mp3")
             << QUrl::fromLocalFile("..\\cPiano\\sounds\\B6.mp3");

    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;

    playlist->addMedia(filelist);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    player->setPlaylist(playlist);
    player->setVolume(ui->volumeDial->value());
    playlist->setCurrentIndex(key);
    player->play();
}

void MainWindow::whiteNotePressed(QPushButton *button)
{
    button->setStyleSheet("background-color: red; border: 1px solid black;");
}

void MainWindow::whiteNoteReleased(QPushButton *button)
{
    button->setStyleSheet("background-color: white; border: 1px solid black;");
}

void MainWindow::blackNotePressed(QPushButton *button)
{
    button->setStyleSheet("background-color: red; border: 1px solid white;");
}

void MainWindow::blackNoteReleased(QPushButton *button)
{
    button->setStyleSheet("background-color: black; border: 1px solid white;");
}

/* White note pressed */

void MainWindow::on_c1_pressed()
{
    pianoKey(0);
    whiteNotePressed(ui->c1);
}

void MainWindow::on_cSharp1_pressed()
{
    pianoKey(1);
    blackNotePressed(ui->cSharp1);
}

void MainWindow::on_d1_pressed()
{
    pianoKey(2);
    whiteNotePressed(ui->d1);
}

void MainWindow::on_dSharp1_pressed()
{
    pianoKey(3);
    blackNotePressed(ui->dSharp1);
}

void MainWindow::on_e1_pressed()
{
    pianoKey(4);
    whiteNotePressed(ui->e1);
}

void MainWindow::on_f1_pressed()
{
    pianoKey(5);
    whiteNotePressed(ui->f1);
}

void MainWindow::on_fSharp1_pressed()
{
    pianoKey(6);
    blackNotePressed(ui->fSharp1);
}

void MainWindow::on_g1_pressed()
{
    pianoKey(7);
    whiteNotePressed(ui->g1);
}

void MainWindow::on_gSharp1_pressed()
{
    pianoKey(8);
    blackNotePressed(ui->gSharp1);
}

void MainWindow::on_a1_pressed()
{
    pianoKey(9);
    whiteNotePressed(ui->a1);
}

void MainWindow::on_aSharp1_pressed()
{
    pianoKey(10);
    blackNotePressed(ui->aSharp1);
}

void MainWindow::on_b1_pressed()
{
    pianoKey(11);
    whiteNotePressed(ui->b1);
}

void MainWindow::on_c2_pressed()
{
    pianoKey(12);
    whiteNotePressed(ui->c2);
}

void MainWindow::on_cSharp2_pressed()
{
    pianoKey(13);
    blackNotePressed(ui->cSharp2);
}

void MainWindow::on_d2_pressed()
{
    pianoKey(14);
    whiteNotePressed(ui->d2);
}

void MainWindow::on_dSharp2_pressed()
{
    pianoKey(15);
    blackNotePressed(ui->dSharp2);
}

void MainWindow::on_e2_pressed()
{
    pianoKey(16);
    whiteNotePressed(ui->e2);
}

void MainWindow::on_f2_pressed()
{
    pianoKey(17);
    whiteNotePressed(ui->f2);
}

void MainWindow::on_fSharp2_pressed()
{
    pianoKey(18);
    blackNotePressed(ui->fSharp2);
}

void MainWindow::on_g2_pressed()
{
    pianoKey(19);
    whiteNotePressed(ui->g2);
}

void MainWindow::on_gSharp2_pressed()
{
    pianoKey(20);
    blackNotePressed(ui->gSharp2);
}

void MainWindow::on_a2_pressed()
{
    pianoKey(21);
    whiteNotePressed(ui->a2);
}

void MainWindow::on_aSharp2_pressed()
{
    pianoKey(22);
    blackNotePressed(ui->aSharp2);
}

void MainWindow::on_b2_pressed()
{
    pianoKey(23);
    whiteNotePressed(ui->b2);
}

/* White note released */

void MainWindow::on_c1_released()
{
    whiteNoteReleased(ui->c1);
}

void MainWindow::on_cSharp1_released()
{
    blackNoteReleased(ui->cSharp1);
}

void MainWindow::on_d1_released()
{
    whiteNoteReleased(ui->d1);
}

void MainWindow::on_dSharp1_released()
{
    blackNoteReleased(ui->dSharp1);
}

void MainWindow::on_e1_released()
{
    whiteNoteReleased(ui->e1);
}

void MainWindow::on_f1_released()
{
    whiteNoteReleased(ui->f1);
}

void MainWindow::on_fSharp1_released()
{
    blackNoteReleased(ui->fSharp1);
}

void MainWindow::on_g1_released()
{
    whiteNoteReleased(ui->g1);
}

void MainWindow::on_gSharp1_released()
{
    blackNoteReleased(ui->gSharp1);
}

void MainWindow::on_a1_released()
{
    whiteNoteReleased(ui->a1);
}

void MainWindow::on_aSharp1_released()
{
    blackNoteReleased(ui->aSharp1);
}

void MainWindow::on_b1_released()
{
    whiteNoteReleased(ui->b1);
}

void MainWindow::on_c2_released()
{
    whiteNoteReleased(ui->c2);
}

void MainWindow::on_cSharp2_released()
{
    blackNoteReleased(ui->cSharp2);
}

void MainWindow::on_d2_released()
{
    whiteNoteReleased(ui->d2);
}

void MainWindow::on_dSharp2_released()
{
    blackNoteReleased(ui->dSharp2);
}

void MainWindow::on_e2_released()
{
    whiteNoteReleased(ui->e2);
}

void MainWindow::on_f2_released()
{
    whiteNoteReleased(ui->f2);
}

void MainWindow::on_fSharp2_released()
{
    blackNoteReleased(ui->fSharp2);
}

void MainWindow::on_g2_released()
{
    whiteNoteReleased(ui->g2);
}

void MainWindow::on_gSharp2_released()
{
    blackNoteReleased(ui->gSharp2);
}

void MainWindow::on_a2_released()
{
    whiteNoteReleased(ui->a2);
}

void MainWindow::on_aSharp2_released()
{
    blackNoteReleased(ui->aSharp2);
}

void MainWindow::on_b2_released()
{
    whiteNoteReleased(ui->b2);
}
