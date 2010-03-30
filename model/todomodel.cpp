#include "todomodel.h"

#include <QList>
#include <QVariant>
#include <QModelIndex>

TodoModel::TodoModel( QObject* parent )
    : TreeModel(parent)
{
  QList<QVariant> overdueData;
  overdueData << "Overdue" << ""; //second "", because else in children you couldn't have two columns
  QList<QVariant> todayData;
  todayData << "Today" << "";
  QList<QVariant> tomorrowData;
  tomorrowData << "Tomorrow" << "";
  QList<QVariant> thisWeekData;
  thisWeekData << "This Week" << "";
  QList<QVariant> thisMonthData;
  thisMonthData << "This Month" << "";
  QList<QVariant> futureData;
  futureData << "Future" << "";
  overdue = new QModelIndex( addItem(overdueData, QModelIndex()) );
  today = new QModelIndex( addItem( todayData, QModelIndex()) );
  tomorrow = new QModelIndex( addItem(tomorrowData, QModelIndex()) );
  thisWeek = new QModelIndex( addItem(thisWeekData, QModelIndex()) );
  thisMonth = new QModelIndex( addItem(thisMonthData, QModelIndex()) );
  future = new QModelIndex( addItem(futureData, QModelIndex()) );
}

TodoModel::~TodoModel()
{
}

void TodoModel::addTodo( TodoObject object )
{
  QList<QVariant> data;
  data << object.getName() << object.getDate().toString("ddd, dd.MMM yyyy");
  int days = QDate::currentDate().daysTo( object.getDate() );
  if( days < 0 ){
    addItem(data, *overdue);
    return;
  }
  if( days == 0 ){
    addItem( data, *today );
    return;
  }
  if( days == 1 ){
    addItem( data, *tomorrow );
    return;
  }
  if( days < 7 ){
    addItem( data, *thisWeek );
    return;
  }
  if( days < 31 ){
    addItem( data, *thisMonth );
    return;
  }
  addItem( data, *future );
}
