#include "accompagnant.h"
#include<QSqlQuery>
#include<QDebug>
#include<QObject>

accompagnant::accompagnant()
{
id=0, email=" ",adresse=" ",num=0,nom=" ",relation=" ";
}

accompagnant::accompagnant(int id,QString email,QString adresse,int num,QString nom,QString relation)
{this->id=id;this->email=email;this->adresse=adresse;this->num=num;this->nom=nom;this->relation=relation;}

                    /* ##########     GET     ########## */

int accompagnant::getid(){return id;}
QString accompagnant::getemail(){return email;}
QString accompagnant::getadresse(){return adresse;}
int accompagnant::getnum(){return num;}
QString accompagnant::getnom(){return nom;}
QString accompagnant::getrelation(){return relation;}

                    /* ##########     SET     ########## */

void accompagnant::setid(int id){this->id=id;}
void accompagnant::setemail(QString email){this->email=email;}
void accompagnant::setadresse(QString adresse){this->adresse=adresse;}
void accompagnant::setnum(int num){this->num=num;}
void accompagnant::setnom(QString nom){this->nom=nom;}
void accompagnant::setrelation(QString relation){this->relation=relation;}

bool accompagnant::ajouter(){
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO accompagnant (id, email, adresse, num, nom, relation) "
                        "VALUES (:id, :email, :adresse, :num, :nom, :relation)");
          query.bindValue(":id", id_string);
          query.bindValue(":email", email);
          query.bindValue(":adresse", adresse);
          query.bindValue(":num", num);
          query.bindValue(":nom", nom);
          query.bindValue(":relation", relation);
    return query.exec();
}

bool accompagnant::supprimer(int id)
{
    QSqlQuery query;
          query.prepare("Delete from accompagnant where id = :id");
          query.bindValue(0, id);
    return query.exec();


}

QSqlQueryModel* accompagnant::afficher(){

              QSqlQueryModel* model=new QSqlQueryModel();
                   model->setQuery("SELECT * FROM accompagnant");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));
              return model;
}

bool accompagnant::modifier(int id ,QString email,QString adresse,int num,QString nom,QString relation)
          {
              QSqlQuery query;
              query.prepare("UPDATE accompagnant SET id= :id,email= :email,adresse = :adresse,num=:num,nom=:nom,relation=:relation  WHERE id= :id ");
              query.bindValue(":id",id);
              query.bindValue(":email",email);
              query.bindValue(":adresse",adresse);
              query.bindValue(":num",num);
              query.bindValue(":nom",nom);
              query.bindValue(":relation",relation);

              return    query.exec();
          }

// rech
QSqlQueryModel *accompagnant::afficher_id(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM accompagnant where id= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));
          return model ;
}
QSqlQueryModel *accompagnant::afficher_nom(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM accompagnant where nom= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));
          return model ;
}
QSqlQueryModel *accompagnant:: afficher_relation(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM accompagnant where relation= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

    return model ;

}

//pdf
QSqlQueryModel * accompagnant:: getAllId(){
    QSqlQueryModel * model =new QSqlQueryModel();
            model->setQuery("select id from accompagnant ");
            return model ;
}

accompagnant* accompagnant::readaccompagnant (QString val)
{
 QSqlQuery query;
    query.prepare("Select * FROM accompagnant where id='"+val+"'");
        if(query.exec())
        {     while(query.next())
            {
             setid(query.value(0).toInt());
             setemail(query.value(1).toString());
             setadresse(query.value(2).toString());
             setnum (query.value(3).toInt());
             setnom(query.value(4).toString());
             setrelation(query.value(5).toString());
            }
        }
     return this;
}
//tri

QSqlQueryModel *accompagnant:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

     if(choix=="ID croissants")
    {
        model->setQuery("SELECT * FROM accompagnant  ORDER BY id ASC ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

    }
     else if(choix=="ID decroissant")
     {
         model->setQuery("SELECT * FROM accompagnant  ORDER BY id DESC;");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

     }else if(choix=="Relation croissant")
     {
         model->setQuery("SELECT * FROM accompagnant  ORDER BY relation ASC;");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

     }
     else if(choix=="Relation decroissant")
     {
         model->setQuery("SELECT * FROM accompagnant ORDER BY relation DESC;");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

     }
    else if (choix=="choisir")
    {
        model->setQuery("SELECT * FROM accompagnant ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("E-mail"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Relation"));

    }


    return model;
}

//stat

int accompagnant::statistique1(){
    QSqlQuery query;
            int count=0 ;
            QSqlQuery requete("select * from accompagnant where relation like 'parent'") ;
            while(requete.next())
            {
                    count++ ;
            }

        return count ;
}

int accompagnant::statistique2(){
    QSqlQuery query;
            int count=0 ;
            QSqlQuery requete("select * from accompagnant where relation like 'autre'") ;
            while(requete.next())
            {
                    count++ ;
            }

        return count ;
}

