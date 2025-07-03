#ifndef FORMULARIOOBJETO_H
#define FORMULARIOOBJETO_H

#include <QWidget>
#include <QMessageBox>
#include "DatabaseManager.h"
#include <QDateTime>
#include "Objeto.h"

namespace Ui {
class FormularioObjeto;
}

class FormularioObjeto : public QWidget
{
    Q_OBJECT

public:
    explicit FormularioObjeto(QWidget *parent = nullptr);
    explicit FormularioObjeto(int usuarioId, QWidget *parent = nullptr);
    ~FormularioObjeto();

private slots:
    void on_pushButtonGuardar_clicked();    // Qt conecta automáticamente
    void on_pushButtonLimpiar_clicked();    // por el nombre del botón

private:
    Ui::FormularioObjeto *ui;
    DatabaseManager *db;
    int usuarioActualId;
};

#endif // FORMULARIOOBJETO_H
