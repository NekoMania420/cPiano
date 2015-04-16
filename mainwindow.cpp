#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "shortcutdialog.h"
#include <QThread>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set volume value at volume label.
    ui->volumeValue->setText(QString::number(ui->volumeSlider->value()));

    // Get directory lists from 'sounds' folder and show in 'Sound select'.
    refreshList();

    // Create time object for using with error text.
    timer = new QTimer(this);

    // Connect octave value to piano label.
    // When you change octave value in each row,
    // octave labels in that row will be changed.
    connect(ui->lowerOctave, SIGNAL(valueChanged(int)), this, SLOT(lowerPianoLabelOctave()));
    connect(ui->upperOctave, SIGNAL(valueChanged(int)), this, SLOT(upperPianoLabelOctave()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshList()
{
    // Keep current selected list's text for using select list when you
    // press refresh button or initialize when program is starting.
    QString latestSelected;
    if (ui->soundSelector->currentRow() >= 0)
    {
        latestSelected = ui->soundSelector->currentItem()->text();
    }

    // Clear old list.
    ui->soundSelector->clear();

    // Get list from 'sounds' directory.
    QDir currentDir(QApplication::applicationDirPath() + "\\sounds");
    currentDir.setFilter(QDir::AllDirs | QDir::NoSymLinks);

    QFileInfoList soundListDir = currentDir.entryInfoList();

    QStringList soundBank;
    for (int i = 0; i < soundListDir.size(); i++)
    {
        if (!(soundListDir[i].fileName() == "." || soundListDir[i].fileName() == ".."))
        {
            soundBank << soundListDir[i].fileName();
        }
    }

    // Add items to list.
    ui->soundSelector->addItems(soundBank);

    // Set tooltip in each item.
    for (int i = 0; i < soundBank.size(); i++)
    {
        ui->soundSelector->item(i)->setToolTip(soundBank[i]);
    }

    // Check whether have items or not.
    // If item has none, show error text and set all piano keys to be unclickable.
    // Otherwise, set all piano keys to be clickable and select latest sound you selected.
    if (ui->soundSelector->count() == 0)
    {
        ui->currentSoundBank->setText("<b style=\"color: red;\">No sound list!</b>");
        pianoButtonClickable(false);
    }
    else
    {
        pianoButtonClickable(true);

        bool found = false;
        for (int i = 0; i < ui->soundSelector->count(); i++)
        {
            if (ui->soundSelector->item(i)->text() == latestSelected)
            {
                ui->soundSelector->setCurrentRow(i);
                found = true;
                break;
            }
        }

        if (!found)
        {
            ui->soundSelector->setCurrentRow(0);
        }
    }
}

void MainWindow::pianoKey(int key)
{
    // Separate sound key by key.
    if (ui->nonStackableKeys->isChecked())
    {
        for (int i = 0; i < 24; i++)
        {
            p[i].pause();
        }
    }

    // Set file names and check if exists.
    QString path = QApplication::applicationDirPath();
    QString soundListDir = ui->soundSelector->currentItem()->text();
    QString currentPath = path + "\\sounds\\" + soundListDir + "\\";

    QStringList filename;

    filename << "C"  + QString::number(ui->lowerOctave->value())
             << "Cs" + QString::number(ui->lowerOctave->value())
             << "D"  + QString::number(ui->lowerOctave->value())
             << "Ds" + QString::number(ui->lowerOctave->value())
             << "E"  + QString::number(ui->lowerOctave->value())
             << "F"  + QString::number(ui->lowerOctave->value())
             << "Fs" + QString::number(ui->lowerOctave->value())
             << "G"  + QString::number(ui->lowerOctave->value())
             << "Gs" + QString::number(ui->lowerOctave->value())
             << "A"  + QString::number(ui->lowerOctave->value())
             << "As" + QString::number(ui->lowerOctave->value())
             << "B"  + QString::number(ui->lowerOctave->value())
             << "C"  + QString::number(ui->upperOctave->value())
             << "Cs" + QString::number(ui->upperOctave->value())
             << "D"  + QString::number(ui->upperOctave->value())
             << "Ds" + QString::number(ui->upperOctave->value())
             << "E"  + QString::number(ui->upperOctave->value())
             << "F"  + QString::number(ui->upperOctave->value())
             << "Fs" + QString::number(ui->upperOctave->value())
             << "G"  + QString::number(ui->upperOctave->value())
             << "Gs" + QString::number(ui->upperOctave->value())
             << "A"  + QString::number(ui->upperOctave->value())
             << "As" + QString::number(ui->upperOctave->value())
             << "B"  + QString::number(ui->upperOctave->value());

    if (QFile(currentPath + filename[key] + ".wav").exists())
    {
        p[key].setMedia(QUrl::fromLocalFile(currentPath + filename[key] + ".wav"));
        p[key].setVolume(ui->volumeSlider->value());
        p[key].play();
    }
    else
    {
        ui->currentSoundBank->setText("<b style=\"color: red;\">ERROR: File not found.</b>");
        connect(timer, SIGNAL(timeout()), this, SLOT(showCurrentSoundBank()));
        timer->start(1000);
    }
}

void MainWindow::showCurrentSoundBank()
{
    // Show current sound bank you selected.
    ui->currentSoundBank->setText(ui->soundSelector->currentItem()->text());
}

void MainWindow::pianoButtonClickable(bool value)
{
    // Set all keys to be unclickable or not.
    ui->c1->setEnabled(value);
    ui->cSharp1->setEnabled(value);
    ui->d1->setEnabled(value);
    ui->dSharp1->setEnabled(value);
    ui->e1->setEnabled(value);
    ui->f1->setEnabled(value);
    ui->fSharp1->setEnabled(value);
    ui->g1->setEnabled(value);
    ui->gSharp1->setEnabled(value);
    ui->a1->setEnabled(value);
    ui->aSharp1->setEnabled(value);
    ui->b1->setEnabled(value);
    ui->c2->setEnabled(value);
    ui->cSharp2->setEnabled(value);
    ui->d2->setEnabled(value);
    ui->dSharp2->setEnabled(value);
    ui->e2->setEnabled(value);
    ui->f2->setEnabled(value);
    ui->fSharp2->setEnabled(value);
    ui->g2->setEnabled(value);
    ui->gSharp2->setEnabled(value);
    ui->a2->setEnabled(value);
    ui->aSharp2->setEnabled(value);
    ui->b2->setEnabled(value);
}

void MainWindow::lowerPianoLabelOctave()
{
    // Set lower piano labels by octave.
    QString octave(QString::number(ui->lowerOctave->value()));
    ui->cLabel1->setText("C" + octave);
    ui->cSharpLabel1->setText("C#" + octave);
    ui->dLabel1->setText("D" + octave);
    ui->dSharpLabel1->setText("D#" + octave);
    ui->eLabel1->setText("E" + octave);
    ui->fLabel1->setText("F" + octave);
    ui->fSharpLabel1->setText("F#" + octave);
    ui->gLabel1->setText("G" + octave);
    ui->gSharpLabel1->setText("G#" + octave);
    ui->aLabel1->setText("A" + octave);
    ui->aSharpLabel1->setText("A#" + octave);
    ui->bLabel1->setText("B" + octave);
}

void MainWindow::upperPianoLabelOctave()
{
    // Set upper piano labels by octave.
    QString octave(QString::number(ui->upperOctave->value()));
    ui->cLabel2->setText("C" + octave);
    ui->cSharpLabel2->setText("C#" + octave);
    ui->dLabel2->setText("D" + octave);
    ui->dSharpLabel2->setText("D#" + octave);
    ui->eLabel2->setText("E" + octave);
    ui->fLabel2->setText("F" + octave);
    ui->fSharpLabel2->setText("F#" + octave);
    ui->gLabel2->setText("G" + octave);
    ui->gSharpLabel2->setText("G#" + octave);
    ui->aLabel2->setText("A" + octave);
    ui->aSharpLabel2->setText("A#" + octave);
    ui->bLabel2->setText("B" + octave);
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

/*
 * White note and black note pressed
 */

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

/*
 * White note and black note released
 */

void MainWindow::on_c1_released()
{
    whiteNoteReleased(ui->c1);
    if (ui->sustain->isChecked()) p[0].pause();
}

void MainWindow::on_cSharp1_released()
{
    blackNoteReleased(ui->cSharp1);
    if (ui->sustain->isChecked()) p[1].pause();
}

void MainWindow::on_d1_released()
{
    whiteNoteReleased(ui->d1);
    if (ui->sustain->isChecked()) p[2].pause();
}

void MainWindow::on_dSharp1_released()
{
    blackNoteReleased(ui->dSharp1);
    if (ui->sustain->isChecked()) p[3].pause();
}

void MainWindow::on_e1_released()
{
    whiteNoteReleased(ui->e1);
    if (ui->sustain->isChecked()) p[4].pause();
}

void MainWindow::on_f1_released()
{
    whiteNoteReleased(ui->f1);
    if (ui->sustain->isChecked()) p[5].pause();
}

void MainWindow::on_fSharp1_released()
{
    blackNoteReleased(ui->fSharp1);
    if (ui->sustain->isChecked()) p[6].pause();
}

void MainWindow::on_g1_released()
{
    whiteNoteReleased(ui->g1);
    if (ui->sustain->isChecked()) p[7].pause();
}

void MainWindow::on_gSharp1_released()
{
    blackNoteReleased(ui->gSharp1);
    if (ui->sustain->isChecked()) p[8].pause();
}

void MainWindow::on_a1_released()
{
    whiteNoteReleased(ui->a1);
    if (ui->sustain->isChecked()) p[9].pause();
}

void MainWindow::on_aSharp1_released()
{
    blackNoteReleased(ui->aSharp1);
    if (ui->sustain->isChecked()) p[10].pause();
}

void MainWindow::on_b1_released()
{
    whiteNoteReleased(ui->b1);
    if (ui->sustain->isChecked()) p[11].pause();
}

void MainWindow::on_c2_released()
{
    whiteNoteReleased(ui->c2);
    if (ui->sustain->isChecked()) p[12].pause();
}

void MainWindow::on_cSharp2_released()
{
    blackNoteReleased(ui->cSharp2);
    if (ui->sustain->isChecked()) p[13].pause();
}

void MainWindow::on_d2_released()
{
    whiteNoteReleased(ui->d2);
    if (ui->sustain->isChecked()) p[14].pause();
}

void MainWindow::on_dSharp2_released()
{
    blackNoteReleased(ui->dSharp2);
    if (ui->sustain->isChecked()) p[15].pause();
}

void MainWindow::on_e2_released()
{
    whiteNoteReleased(ui->e2);
    if (ui->sustain->isChecked()) p[16].pause();
}

void MainWindow::on_f2_released()
{
    whiteNoteReleased(ui->f2);
    if (ui->sustain->isChecked()) p[17].pause();
}

void MainWindow::on_fSharp2_released()
{
    blackNoteReleased(ui->fSharp2);
    if (ui->sustain->isChecked()) p[18].pause();
}

void MainWindow::on_g2_released()
{
    whiteNoteReleased(ui->g2);
    if (ui->sustain->isChecked()) p[19].pause();
}

void MainWindow::on_gSharp2_released()
{
    blackNoteReleased(ui->gSharp2);
    if (ui->sustain->isChecked()) p[20].pause();
}

void MainWindow::on_a2_released()
{
    whiteNoteReleased(ui->a2);
    if (ui->sustain->isChecked()) p[21].pause();
}

void MainWindow::on_aSharp2_released()
{
    blackNoteReleased(ui->aSharp2);
    if (ui->sustain->isChecked()) p[22].pause();
}

void MainWindow::on_b2_released()
{
    whiteNoteReleased(ui->b2);
    if (ui->sustain->isChecked()) p[23].pause();
}

/*
 * Key events
 */

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->soundSelector->count() != 0)
    {
        if (!event->isAutoRepeat())
        {
            switch (event->key())
            {
            case Qt::Key_Z:
                pianoKey(0);
                whiteNotePressed(ui->c1);
                break;

            case Qt::Key_S:
                pianoKey(1);
                blackNotePressed(ui->cSharp1);
                break;

            case Qt::Key_X:
                pianoKey(2);
                whiteNotePressed(ui->d1);
                break;

            case Qt::Key_D:
                pianoKey(3);
                blackNotePressed(ui->dSharp1);
                break;

            case Qt::Key_C:
                pianoKey(4);
                whiteNotePressed(ui->e1);
                break;

            case Qt::Key_V:
                pianoKey(5);
                whiteNotePressed(ui->f1);
                break;

            case Qt::Key_G:
                pianoKey(6);
                blackNotePressed(ui->fSharp1);
                break;

            case Qt::Key_B:
                pianoKey(7);
                whiteNotePressed(ui->g1);
                break;

            case Qt::Key_H:
                pianoKey(8);
                blackNotePressed(ui->gSharp1);
                break;

            case Qt::Key_N:
                pianoKey(9);
                whiteNotePressed(ui->a1);
                break;

            case Qt::Key_J:
                pianoKey(10);
                blackNotePressed(ui->aSharp1);
                break;

            case Qt::Key_M:
                pianoKey(11);
                whiteNotePressed(ui->b1);
                break;

            case Qt::Key_Q:
                pianoKey(12);
                whiteNotePressed(ui->c2);
                break;

            case Qt::Key_2:
                pianoKey(13);
                blackNotePressed(ui->cSharp2);
                break;

            case Qt::Key_W:
                pianoKey(14);
                whiteNotePressed(ui->d2);
                break;

            case Qt::Key_3:
                pianoKey(15);
                blackNotePressed(ui->dSharp2);
                break;

            case Qt::Key_E:
                pianoKey(16);
                whiteNotePressed(ui->e2);
                break;

            case Qt::Key_R:
                pianoKey(17);
                whiteNotePressed(ui->f2);
                break;

            case Qt::Key_5:
                pianoKey(18);
                blackNotePressed(ui->fSharp2);
                break;

            case Qt::Key_T:
                pianoKey(19);
                whiteNotePressed(ui->g2);
                break;

            case Qt::Key_6:
                pianoKey(20);
                blackNotePressed(ui->gSharp2);
                break;

            case Qt::Key_Y:
                pianoKey(21);
                whiteNotePressed(ui->a2);
                break;

            case Qt::Key_7:
                pianoKey(22);
                blackNotePressed(ui->aSharp2);
                break;

            case Qt::Key_U:
                pianoKey(23);
                whiteNotePressed(ui->b2);
                break;
            }
        }
    }

    switch (event->key())
    {
    case Qt::Key_Minus:
        ui->upperOctave->setValue(ui->upperOctave->value() - 1);
        break;

    case Qt::Key_Equal:
        ui->upperOctave->setValue(ui->upperOctave->value() + 1);
        break;

    case Qt::Key_BracketLeft:
        ui->lowerOctave->setValue(ui->lowerOctave->value() - 1);
        break;

    case Qt::Key_BracketRight:
        ui->lowerOctave->setValue(ui->lowerOctave->value() + 1);
        break;

    case Qt::Key_PageDown:
        ui->volumeSlider->setValue(ui->volumeSlider->value() - 5);
        break;

    case Qt::Key_PageUp:
        ui->volumeSlider->setValue(ui->volumeSlider->value() + 5);
        break;

    case Qt::Key_F5:
        refreshList();
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (ui->soundSelector->count() != 0)
    {
        if (!event->isAutoRepeat())
        {
            switch (event->key())
            {
            case Qt::Key_Z:
                whiteNoteReleased(ui->c1);
                if (ui->sustain->isChecked()) p[0].pause();
                break;

            case Qt::Key_S:
                blackNoteReleased(ui->cSharp1);
                if (ui->sustain->isChecked()) p[1].pause();
                break;

            case Qt::Key_X:
                whiteNoteReleased(ui->d1);
                if (ui->sustain->isChecked()) p[2].pause();
                break;

            case Qt::Key_D:
                blackNoteReleased(ui->dSharp1);
                if (ui->sustain->isChecked()) p[3].pause();
                break;

            case Qt::Key_C:
                whiteNoteReleased(ui->e1);
                if (ui->sustain->isChecked()) p[4].pause();
                break;

            case Qt::Key_V:
                whiteNoteReleased(ui->f1);
                if (ui->sustain->isChecked()) p[5].pause();
                break;

            case Qt::Key_G:
                blackNoteReleased(ui->fSharp1);
                if (ui->sustain->isChecked()) p[6].pause();
                break;

            case Qt::Key_B:
                whiteNoteReleased(ui->g1);
                if (ui->sustain->isChecked()) p[7].pause();
                break;

            case Qt::Key_H:
                blackNoteReleased(ui->gSharp1);
                if (ui->sustain->isChecked()) p[8].pause();
                break;

            case Qt::Key_N:
                whiteNoteReleased(ui->a1);
                if (ui->sustain->isChecked()) p[9].pause();
                break;

            case Qt::Key_J:
                blackNoteReleased(ui->aSharp1);
                if (ui->sustain->isChecked()) p[10].pause();
                break;

            case Qt::Key_M:
                whiteNoteReleased(ui->b1);
                if (ui->sustain->isChecked()) p[11].pause();
                break;

            case Qt::Key_Q:
                whiteNoteReleased(ui->c2);
                if (ui->sustain->isChecked()) p[12].pause();
                break;

            case Qt::Key_2:
                blackNoteReleased(ui->cSharp2);
                if (ui->sustain->isChecked()) p[13].pause();
                break;

            case Qt::Key_W:
                whiteNoteReleased(ui->d2);
                if (ui->sustain->isChecked()) p[14].pause();
                break;

            case Qt::Key_3:
                blackNoteReleased(ui->dSharp2);
                if (ui->sustain->isChecked()) p[15].pause();
                break;
            case Qt::Key_E:
                whiteNoteReleased(ui->e2);
                if (ui->sustain->isChecked()) p[16].pause();
                break;

            case Qt::Key_R:
                whiteNoteReleased(ui->f2);
                if (ui->sustain->isChecked()) p[17].pause();
                break;

            case Qt::Key_5:
                blackNoteReleased(ui->fSharp2);
                if (ui->sustain->isChecked()) p[18].pause();
                break;

            case Qt::Key_T:
                whiteNoteReleased(ui->g2);
                if (ui->sustain->isChecked()) p[19].pause();
                break;

            case Qt::Key_6:
                blackNoteReleased(ui->gSharp2);
                if (ui->sustain->isChecked()) p[20].pause();
                break;

            case Qt::Key_Y:
                whiteNoteReleased(ui->a2);
                if (ui->sustain->isChecked()) p[21].pause();
                break;

            case Qt::Key_7:
                blackNoteReleased(ui->aSharp2);
                if (ui->sustain->isChecked()) p[22].pause();
                break;

            case Qt::Key_U:
                whiteNoteReleased(ui->b2);
                if (ui->sustain->isChecked()) p[23].pause();
                break;
            }
        }
    }
}

void MainWindow::on_action_About_triggered()
{
    // Show about dialog
    AboutDialog about;
    about.exec();
}

void MainWindow::on_refreshSoundList_clicked()
{
    // Refresh when you click refresh button.
    refreshList();
}

void MainWindow::on_actionShortcut_key_triggered()
{
    ShortcutDialog shortcut;
    shortcut.exec();
}
