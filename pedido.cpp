#include "pedido.h"
#include "ui_pedido.h"
#include <QTableWidgetItem>

pedido::pedido(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::pedido)
{
   ui->setupUi(this);
   QStringList titles;
    titles<<"  Id_pedido"<<" cliente"<<" camarero"<<"cheff"<<" fecha"<<"hora"<<"estado";
   ui->tableWidget->setColumnCount(7);
   ui->tableWidget->setHorizontalHeaderLabels(titles);
    start();
    second();
}

string pedido::leer1()
{
      ifstream ifsInt ("cliente.txt");
      string str;
      getline(ifsInt,str);
      ifsInt.close();
      return  str ;
}

void pedido::start()
{
ui->tableWidget->setRowCount(0);
  string consulta;
 QString id, cliente, camarero, cheff, fecha, hora, estado;
 consulta="select  id_pedido, cliente.nombre, camarero.nombre, cheff.nombre, fecha, hora, pedido.estado from pedido join cliente on cliente.id_cliente=pedido.id_cliente join camarero on camarero.id_camarero=pedido.id_camarero join cheff on cheff.id_cheff=pedido.id_cheff order by id_pedido";

  res=PQexec(conn,consulta.c_str());
 int cont, ntuples;
 for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
 {
       id= PQgetvalue(res,cont,0);cliente= PQgetvalue(res,cont,1);camarero= PQgetvalue(res,cont,2);
       cheff=PQgetvalue(res,cont,3);fecha=PQgetvalue(res,cont,4);hora=PQgetvalue(res,cont,5);estado=PQgetvalue(res,cont,6);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0 ,  new QTableWidgetItem(id));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1 ,  new QTableWidgetItem(cliente));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2 ,  new QTableWidgetItem(camarero));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3 ,  new QTableWidgetItem(cheff));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4 ,  new QTableWidgetItem(fecha));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5 ,  new QTableWidgetItem(hora));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6 ,  new QTableWidgetItem(estado));
   }
  PQclear(res);
}



void pedido::on_buscar_clicked()
{
  ui->tableWidget->setRowCount(0);
  QString fechape,horape,clientepe,camarerope ;
  string sfecha,shora,scliente,scamarero,consulta;
  fechape=ui->fecha->text();  horape=ui->hora->text();
  clientepe=ui->id_cliente->text();  camarerope=ui->id_camarero->text();
  sfecha= fechape.toUtf8().constData();  shora= horape.toUtf8().constData();
  scamarero= camarerope.toUtf8().constData();  scliente= clientepe.toUtf8().constData();
  if(scliente.empty() )
  consulta="select  id_pedido, cliente.nombre, camarero.nombre, cheff.nombre, fecha, hora, pedido.estado from pedido join cliente on cliente.id_cliente=pedido.id_cliente and   join camarero on camarero.id_camarero=pedido.id_camarero and camarero.nombre LIKE'%" +scamarero+"%' join cheff on cheff.id_cheff=pedido.id_cheff order by id_pedido";
   if(scamarero.empty())
  consulta="select  id_pedido, cliente.nombre, camarero.nombre, cheff.nombre, fecha, hora, pedido.estado from pedido join cliente on cliente.id_cliente=pedido.id_cliente and cliente.nombre LIKE '%" +scliente+"%'  join camarero on camarero.id_camarero=pedido.id_camarero join cheff on cheff.id_cheff=pedido.id_cheff order by id_pedido";
   if(sfecha.empty()) sfecha= "01-01-01";
  if(shora.empty() ) shora = "01:00:00";
 consulta="select  id_pedido, cliente.nombre, camarero.nombre, cheff.nombre, fecha, hora, pedido.estado from pedido join cliente on cliente.id_cliente=pedido.id_cliente and cliente.nombre LIKE '%" +scliente+"%'  join camarero on camarero.id_camarero=pedido.id_camarero and camarero.nombre LIKE'%" +scamarero+"%' join cheff on cheff.id_cheff=pedido.id_cheff order by id_pedido";
  //consulta="select  id_pedido, cliente, camarero, id_cheff,fecha, hora ,estado from pedido where fecha>'"+sfecha+"' and hora>'" +shora+"'  ";
 res=PQexec(conn,consulta.c_str());
  //ui->ayuda->setText(QString::fromStdString(consulta));
 QString id, cliente, camarero, cheff, fecha, hora, estado;
 int cont, ntuples;
 for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
 {
       id= PQgetvalue(res,cont,0); cliente= PQgetvalue(res,cont,1); camarero= PQgetvalue(res,cont,2);
       cheff=PQgetvalue(res,cont,3); fecha=PQgetvalue(res,cont,4);hora=PQgetvalue(res,cont,5);estado=PQgetvalue(res,cont,6);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0 ,  new QTableWidgetItem(id));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1 ,  new QTableWidgetItem(cliente));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2 ,  new QTableWidgetItem(camarero));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3 ,  new QTableWidgetItem(cheff));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4 ,  new QTableWidgetItem(fecha));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5 ,  new QTableWidgetItem(hora));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6 ,  new QTableWidgetItem(estado));
   }
 ui->fecha->setText(""); ui->hora->setText(""); ui->id_cliente->setText(""); ui->id_camarero->setText("");
 PQclear(res);

}

void pedido::on_ver_clicked()
{
    guardar(to_string(indecito));
    detalle * detalle1 = new detalle();
    detalle1->show();
}

void pedido::second()
{
   string str [3];
    str[0]="select id_mesa from mesa";
    str[1]="select nombre from camarero";
     str[2]="select  nombre from cheff";

       QString  tmp;  int cont, ntuples;

       ui->mesa->addItem(""); res=PQexec(conn,str[0].c_str());
       for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
               tmp= PQgetvalue(res,cont,0),ui->mesa->addItem(tmp);

       ui->camarero->addItem(""); res=PQexec(conn,str[1].c_str());
       for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
               tmp= PQgetvalue(res,cont,0), ui->camarero->addItem(tmp);

       ui->cheff->addItem(""); res=PQexec(conn,str[2].c_str());
       for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
               tmp= PQgetvalue(res,cont,0), ui->cheff->addItem(tmp);
       PQclear(res);

}

void pedido::on_agregar_clicked()
{
  leer_platos();
  QString ca,ch; string sca,sch,sm, scl, cc,ccc,cm;
  list.push_back(ui->mesa->currentText()); cm=(list[0].toUtf8().constData());
  list.push_back(ui->camarero->currentText());cc=(list[1].toUtf8().constData());
  list.push_back(ui->cheff->currentText());ccc=(list[2].toUtf8().constData());
  string scamarero="select id_camarero from camarero where nombre='"+cc+"'";
  res=PQexec(conn,scamarero.c_str());ca=PQgetvalue(res, 0, 0);
  string scheff="select id_cheff from cheff where nombre='"+ccc+"'";
  res=PQexec(conn,scheff.c_str()); ch=PQgetvalue(res, 0, 0);
  sca=(ca.toUtf8().constData());sch=(ch.toUtf8().constData());
  //ui->ayuda2->setText(ca);
  sm=(list[2].toUtf8().constData()); scl= (leer1());
  string  insert="insert into pedido(fecha, hora, id_cliente, id_camarero ,id_cheff, estado) values (current_date,current_time,'"+scl+"' ,'"+sca+"','"+sch+"','true')";
 res=PQexec(conn,insert.c_str());  start();
  //ui->ayuda->setText(QString::fromStdString(insert));
  string   consulta="select  id_pedido from pedido order by pedido";res=PQexec(conn,consulta.c_str());
  QString ped=PQgetvalue(res,PQntuples(res)-1,0);string pedi=ped.toUtf8().constData();
  for(int i=0;i<index_platos.size();i+=2)
    {
      string insert_plato;
      for(int j=0;j<index_platos[i+1];j++)
          insert_plato="insert into pedido_detalle(id_pedido,id_plato,id_mesa) values('" +pedi+"','"+to_string(index_platos[i])+"', '" +cm +"' )", res=PQexec(conn,insert_plato.c_str());
      }
}

void pedido::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
int it =item->row();
index.push_back(it);
  QString ittemm= ui->tableWidget->item(it,0)->text();
 string str=ittemm.toUtf8().constData();
 indecito=stoi(str);
 index2.push_back(indecito);

}

pedido::~pedido()
{
  delete ui;
}

void pedido::guardar(string palabra)
{
ofstream ofs("index.txt");
ofs<<palabra;
ofs.close();
}

void pedido::on_Cliente_clicked()
{
    Cliente * cliente1 = new Cliente();
    cliente1->show();
}

void pedido::on_Platos_clicked()
{
platos * platos1=new platos();
 platos1->show();
}

void pedido::leer_platos()
{
       ifstream text("platitos.txt");
          string word;
          while(text >> word)
                   index_platos.push_back(stoi(word));
         text.close();
}

void pedido::on_buscar_2_clicked()
{
    start();
}
