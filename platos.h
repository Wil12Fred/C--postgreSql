#ifndef PLATOS_H
#define PLATOS_H

#include <QMainWindow>
#include <QTableView>
#include <QTableWidgetItem>
#include <postgresql/libpq-fe.h>
#include <string>
#include <vector>
#include <cliente.h>
#include <detalle.h>
#include <ui_mainwindow.h>
#include <fstream>
#include <sstream>
#include "cliente.h"

namespace Ui {
  class platos;
}

class platos : public QMainWindow
{
  Q_OBJECT

public:
       PGconn *conn= PQconnectdb("dbname=Restaurant host=localhost user=postgres password='ltch23. '");
       PGresult  *res;
       vector<int> index;
       vector<int> index2;
       vector<int> codes;
      void guardar_plato();
       void start();

  explicit platos(QWidget *parent = 0);
  ~platos();

private slots:
  void on_buscar_plato_clicked();
  void on_aceptar_plato_clicked();

  void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
  Ui::platos *ui;
};

#endif // PLATOS_H

