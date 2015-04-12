#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void pianoKey(int key);
    void whiteNotePressed(QPushButton *button);
    void whiteNoteReleased(QPushButton *button);
    void blackNotePressed(QPushButton *button);
    void blackNoteReleased(QPushButton *button);

private slots:
    void on_c1_pressed();
    void on_cSharp1_pressed();
    void on_d1_pressed();
    void on_dSharp1_pressed();
    void on_e1_pressed();
    void on_f1_pressed();
    void on_fSharp1_pressed();
    void on_g1_pressed();
    void on_gSharp1_pressed();
    void on_a1_pressed();
    void on_aSharp1_pressed();
    void on_b1_pressed();

    void on_c2_pressed();
    void on_cSharp2_pressed();
    void on_d2_pressed();
    void on_dSharp2_pressed();
    void on_e2_pressed();
    void on_f2_pressed();
    void on_fSharp2_pressed();
    void on_g2_pressed();
    void on_gSharp2_pressed();
    void on_a2_pressed();
    void on_aSharp2_pressed();
    void on_b2_pressed();

    void on_c1_released();
    void on_cSharp1_released();
    void on_d1_released();
    void on_dSharp1_released();
    void on_e1_released();
    void on_f1_released();
    void on_fSharp1_released();
    void on_g1_released();
    void on_gSharp1_released();
    void on_a1_released();
    void on_aSharp1_released();
    void on_b1_released();

    void on_c2_released();
    void on_cSharp2_released();
    void on_d2_released();
    void on_dSharp2_released();
    void on_e2_released();
    void on_f2_released();
    void on_fSharp2_released();
    void on_g2_released();
    void on_gSharp2_released();
    void on_a2_released();
    void on_aSharp2_released();
    void on_b2_released();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
};

#endif // MAINWINDOW_H
