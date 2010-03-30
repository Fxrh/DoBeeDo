#ifndef TODOMODEL_H
#define TODOMODEL_H

#include "treemodel.h"
#include "../todoobject.h"

class TodoModel : public TreeModel
{
    Q_OBJECT
  public:
    TodoModel( QObject* parent = 0 );
    ~TodoModel();
    
    void addTodo( TodoObject object );
    
  private:
    QModelIndex* overdue;
    QModelIndex* today;
    QModelIndex* tomorrow;
    QModelIndex* thisWeek;
    QModelIndex* thisMonth;
    QModelIndex* future;
    
};

#endif //TODOMODEL_H
