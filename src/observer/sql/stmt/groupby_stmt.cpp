#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/groupby_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/stmt/filter_stmt.h"

GroupByStmt::~GroupByStmt()
{
  for (GroupByUnit *unit : groupby_units_) {
    delete unit;
  }
  groupby_units_.clear();
}

RC GroupByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const GroupBy *groupbys, int groupby_num, GroupByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  GroupByStmt *tmp_stmt = new GroupByStmt();
  for (int i = 0; i < groupby_num; i++) {
    GroupByUnit *groupby_unit = nullptr;
    rc = create_groupby_unit(db, default_table, tables, groupbys[i], groupby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create groupby unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->groupby_units_.push_back(groupby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC GroupByStmt::create_groupby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const GroupBy &groupby, GroupByUnit *&groupby_unit)
{
  RC rc = RC::SUCCESS;

  Expression *expr = nullptr;
  Table *table = nullptr;
  const FieldMeta *field = nullptr;
  rc = get_table_and_field(db, default_table, tables, groupby, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  expr = new FieldExpr(table, field);
  groupby_unit = new GroupByUnit;
  groupby_unit->set_expr(expr);
  return rc;
}
