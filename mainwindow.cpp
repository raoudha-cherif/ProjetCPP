#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accompagnant.h"
#include "statistiques.h"
#include <QPrinter>
#include <QPainter>
#include<QIntValidator>
#include<QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_en->setModel(A.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    int id=ui->lineEdit_cin->text().toInt();
    QString email=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_prenom->text();
    int num=ui->spinBox_age->text().toInt();
    QString nom=ui->lineEdit_salaire->text();
    QString relation=ui->lineEdit_email->text();
    accompagnant A(id,email,adresse,num,nom,relation);
    bool test = A.ajouter();
    if(test)
       ui->tableView_en->setModel(A.afficher());
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
                    QObject::tr("Accompagnant Ajouter.\n"), QMessageBox::Ok);


}
}

void MainWindow::on_pushButton_Annuler_clicked()
{
    close();
}

void MainWindow::on_pushButton_annulersup_clicked()
{
    close();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
 accompagnant A1 ;
 A1.setid(ui->lineEdit_supp->text().toInt());
 bool test = A1.supprimer(A1.getid());
 if(test)
     ui->tableView_en->setModel(A.afficher());
 {
     QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                 QObject::tr("Suppression Terminer.\n"), QMessageBox::Ok);

}
}


void MainWindow::on_pushButton_Edit_clicked()
{
    int id=ui->lineEdit_id_edit->text().toInt();
    QString email=ui->lineEdit_nom_edit->text();
    QString adresse=ui->lineEdit_prenom_edit->text();
    int num=ui->spinBox_age_edit->text().toInt();
    QString nom=ui->lineEdit_salaire_edit->text();
    QString relation=ui->lineEdit_email_edit->text();



                accompagnant A;
                bool test=A.modifier(id,email,adresse,num,nom,relation);

                if(test)
                ui->tableView_en->setModel(A.afficher());
                {

                    QMessageBox::information(nullptr, QObject::tr("modifie un accompagnant"),
                                      QObject::tr("accompagnant modifiée.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tableView_en->setModel(A.afficher());

               }
}


void MainWindow::on_rech_clicked()
{
    QString val=ui->le_rech->text();
    QString option=ui->cb_rech_emp->currentText();
    if((val!="")&&(option=="id"))
{        ui->tableView_en->setModel(A.afficher_id(val));}
    else if((val!="")&&(option=="nom"))
    {
             ui->tableView_en->setModel(A.afficher_nom(val));
    }
    else if((val!="")&&(option=="relation"))
    {
               ui->tableView_en->setModel(A.afficher_relation(val));
    }else if(option=="choisir")
    {
       ui->tableView_en->setModel(A.afficher());
    }
}
void MainWindow::on_pdf_push_clicked()
{
    QString id_cb=ui->pdf_c->text();
      accompagnant * ac ;
    ac=A.readaccompagnant(id_cb);
    QString id_string=QString::number(ac->getid());
    QString email_string = ac->getemail();
    QString adresse_string = ac->getadresse();
    QString num_string=QString::number(ac->getnum());
    QString nom_string= ac->getnom();
    QString relation_string= ac->getrelation();

     QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C:/Users/raoud/Desktop/pdf_projet/"+id_string+".pdf");
                           QPainter painter;
                           if(! painter.begin(&printer))
                           { qWarning("failed to open file");  }
                            painter.setFont(QFont("Sitka Heading", 25));
                            painter.setPen(Qt::blue);
                            painter.drawText(420,100," ADPH ");
                            painter.setPen(Qt::black);
                            painter.drawText(175,50,"Information relative à l'accompagnant");
                            painter.setPen(Qt::black);
                            painter.drawText(250,300,"Identifiant : " + id_string);
                            painter.drawText(250,400,"E-mail : "+email_string);
                            painter.drawText(250,500,"Adresse : "+adresse_string);
                            painter.drawText(250,600,"Num : " +num_string);
                            painter.drawText(250,700,"Nom : "+nom_string);
                            painter.drawText(250,800,"Relation : "+relation_string);
                            painter.end();
}

void MainWindow::on_cb_tri_activated(const QString &arg1)
{
    QString choix=ui->cb_tri->currentText();
    ui->tableView_en->setModel(A.afficher_choix(choix));
}

void MainWindow::on_pb_stat_clicked()
{
     statistiques S;
     S.setModal(true);
     S.exec();
}
