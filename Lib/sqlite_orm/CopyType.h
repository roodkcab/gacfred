//
// Created by css on 23-2-1.
//

#pragma once

#include "UI/Source/Gacfred.h"
#include <sqlite_orm/sqlite_orm.h>

using namespace vl;
using namespace sqlite_orm;

namespace sqlite_orm {

    template<>
    struct type_printer<gacfred::CopyType> : public integer_printer{};

    template<>
    struct statement_binder<gacfred::CopyType> {
        int bind(sqlite3_stmt *stmt, int index, const gacfred::CopyType& value) {
            return sqlite3_bind_int(stmt, index++, int(value));
        }
    };

    template<>
    struct field_printer<gacfred::CopyType> {
        std::string operator()(const gacfred::CopyType& t) const {
            return itoa(int(t)).Buffer();
        }
    };

    template<>
    struct row_extractor<gacfred::CopyType> {
        gacfred::CopyType extract(int row_value) {
            return gacfred::CopyType(row_value);
        }

        gacfred::CopyType extract(sqlite3_stmt *stmt, int columnIndex) {
            return gacfred::CopyType(sqlite3_column_int(stmt, columnIndex));
        }
    };
}