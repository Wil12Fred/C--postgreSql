#ifndef DETALLE_H
#define DETALLE_H

#include <QMainWindow>
#include <QTableView>
#include <QTableWidgetItem>
#include <postgresql/libpq-fe.h>
#include "plato.h"
#include <string>
#include <vector>
#include <cliente.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace Ui {
  class detalle;
}

class detalle : public QMainWindow
{
  Q_OBJECT

public:
  explicit detalle(QWidget *parent = 0 );

  void start();
  void start2();
  void leer_platitos();

  PGconn    *conn= PQconnectdb("dbname=Restaurant host=localhost user=postgres password='ltch23. '");
  PGresult  *res;

  vector<int> indexes;
  vector<int> platitos;
  vector<int> index;
  vector<int> index2;
  vector<string>temp;

string leer();
string number;
int indecito;



~detalle();

private slots:
 void on_aceptar_detalle_clicked();
 void on_platos_detalle_clicked();
  void on_eliminar_detalle_clicked();
 void on_agregar_detalle_clicked();
 void on_table2_itemClicked(QTableWidgetItem *item);

private:
  Ui::detalle *ui;
};

#endif // DETALLE_H
