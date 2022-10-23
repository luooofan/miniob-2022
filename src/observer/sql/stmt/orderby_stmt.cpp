#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/orderby_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/stmt/filter_stmt.h"

OrderByStmt::~OrderByStmt()
{
  for (OrderByUnit *unit : orderby_units_) {
    delete unit;
  }
  orderby_units_.clear();
}

RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const OrderBy *orderbys, int orderby_num, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < orderby_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->orderby_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}
RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const GroupBy *groupbys, int groupby_num, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < groupby_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc = create_orderby_unit(db, default_table, tables, groupbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->orderby_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const OrderBy &orderby, OrderByUnit *&orderby_unit)
{
  RC rc = RC::SUCCESS;

  bool sort_type = orderby.is_asc;

  Expression *expr = nullptr;
  Table *table = nullptr;
  const FieldMeta *field = nullptr;
  rc = get_table_and_field(db, default_table, tables, orderby.sort_attr, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  expr = new FieldExpr(table, field);
  orderby_unit = new OrderByUnit;
  orderby_unit->set_sort_type(sort_type);
  orderby_unit->set_expr(expr);
  return rc;
}

RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const GroupBy &groupby, OrderByUnit *&orderby_unit)
{
  RC rc = RC::SUCCESS;

  bool sort_type = true;

  Expression *expr = nullptr;
  Table *table = nullptr;
  const FieldMeta *field = nullptr;
  rc = get_table_and_field(db, default_table, tables, groupby, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  expr = new FieldExpr(table, field);
  orderby_unit = new OrderByUnit;
  orderby_unit->set_sort_type(sort_type);
  orderby_unit->set_expr(expr);
  return rc;
}
