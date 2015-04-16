#include "shortcutdialog.h"
#include "ui_shortcutdialog.h"

ShortcutDialog::ShortcutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortcutDialog)
{
    ui->setupUi(this);
}

ShortcutDialog::~ShortcutDialog()
{
    delete ui;
}
