#ifndef TAGSVIEWFORM_H
#define TAGSVIEWFORM_H

#include <QWidget>

namespace Ui {
class tagsviewform;
}

class tagsviewform : public QWidget
{
    Q_OBJECT

public:
    explicit tagsviewform(QWidget *parent = nullptr);
    ~tagsviewform();
    void setTextBoxValue(const QString &value);

private:
    Ui::tagsviewform *ui;
};

#endif // TAGSVIEWFORM_H
