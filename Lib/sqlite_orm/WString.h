#pragma once

#include "GacUI.h"
#include <string>
#include <sqlite_orm/sqlite_orm.h>

using namespace vl;
using namespace sqlite_orm;

namespace sqlite_orm {

    template<>
    struct type_printer<WString> : public text_printer {};

    template<>
    struct statement_binder<WString> {
        int bind(sqlite3_stmt *stmt, int index, const WString &value) {
            return sqlite3_bind_text(stmt, index++, wtoa(value).Buffer(), -1, SQLITE_TRANSIENT);
        }
    };

    template<>
    struct field_printer<WString> {
        std::string operator()(const WString& t) const {
			return wtoa(t).Buffer();
        }
    };

    template<>
    struct row_extractor<WString> {
        WString extract(sqlite3_stmt *stmt, int columnIndex) {
            return atow((const char *)sqlite3_column_text(stmt, columnIndex));
        }
    };

    template<>
    struct type_is_nullable<WString> : public std::true_type {
        bool operator()(const WString& g) const {
            return g != L"";
        }
    };
}