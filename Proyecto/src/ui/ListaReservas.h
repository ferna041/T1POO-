#ifndef LISTARESERVAS_H
#define LISTARESERVAS_H

#include <QWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>
#include "../database/DatabaseManager.h"
#include "../models/Reserva.h"
#include "../models/Objeto.h"

namespace Ui {
class ListaReservas;
}

class ListaReservas : public QWidget
{
    Q_OBJECT

public:
    explicit ListaReservas(QWidget *parent = nullptr);
    explicit ListaReservas(int usuarioId, QWidget *parent = nullptr);
    ~ListaReservas();

private slots:
    void on_pushButtonActualizar_clicked();
    void cancelarReserva();

private:
    Ui::ListaReservas *ui;
    DatabaseManager *db;
    int usuarioActualId;
    
    void configurarTabla();
    void cargarReservas();
    QPushButton* crearBotonCancelar(int reservaId);
};

#endif // LISTARESERVAS_H
