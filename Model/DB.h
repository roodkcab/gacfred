#pragma once

#include "UI/Source/Gacfred.h"
#include "Model/Copy.h"
#include "Lib/util.h"
#include "Lib/sqlite_orm/CopyType.h"
#include "Lib/sqlite_orm/WString.h"

template <typename... Args>
auto _DB()
{
	return make_storage(wtoa(Appdata(L"/gacfred.db")).Buffer(),
		make_index("idx_ctime", &gacfred::Copy::GetCtime),
		make_table("copies",
            make_column("idx", &gacfred::Copy::GetIdx, &gacfred::Copy::SetIdx, primary_key()),
            make_column("type", &gacfred::Copy::GetType, &gacfred::Copy::SetType),
			make_column("content", &gacfred::Copy::GetContent, &gacfred::Copy::SetContent),
            make_column("ctime", &gacfred::Copy::GetCtime, &gacfred::Copy::SetCtime)
		)
	);
}

static decltype(_DB()) DB()
{
	static decltype(_DB()) db = _DB();
	return db;
}

#define DB DB()
