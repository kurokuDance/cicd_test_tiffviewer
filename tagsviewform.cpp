#include "tagsviewform.h"
#include "ui_tagsviewform.h"

tagsviewform::tagsviewform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tagsviewform)
{
    ui->setupUi(this);
}

tagsviewform::~tagsviewform()
{
    delete ui;
}

void tagsviewform::setTextBoxValue(const QString &value)
{
    ui->tagsValueEdit->setText(value);
}
