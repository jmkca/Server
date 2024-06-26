/**
 * DO NOT MODIFY THIS FILE
 *
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to the repository extending the base.
 * Any modifications to base repositories are to be made by the generator only
 *
 * @generator ./utils/scripts/generators/repository-generator.pl
 * @docs https://docs.eqemu.io/developer/repositories
 */

#ifndef EQEMU_BASE_PETS_EQUIPMENTSET_REPOSITORY_H
#define EQEMU_BASE_PETS_EQUIPMENTSET_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"
#include <ctime>

class BasePetsEquipmentsetRepository {
public:
	struct PetsEquipmentset {
		int32_t     set_id;
		std::string setname;
		int32_t     nested_set;
	};

	static std::string PrimaryKey()
	{
		return std::string("set_id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"set_id",
			"setname",
			"nested_set",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"set_id",
			"setname",
			"nested_set",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(Strings::Implode(", ", Columns()));
	}

	static std::string SelectColumnsRaw()
	{
		return std::string(Strings::Implode(", ", SelectColumns()));
	}

	static std::string TableName()
	{
		return std::string("pets_equipmentset");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			SelectColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			ColumnsRaw()
		);
	}

	static PetsEquipmentset NewEntity()
	{
		PetsEquipmentset e{};

		e.set_id     = 0;
		e.setname    = "";
		e.nested_set = -1;

		return e;
	}

	static PetsEquipmentset GetPetsEquipmentset(
		const std::vector<PetsEquipmentset> &pets_equipmentsets,
		int pets_equipmentset_id
	)
	{
		for (auto &pets_equipmentset : pets_equipmentsets) {
			if (pets_equipmentset.set_id == pets_equipmentset_id) {
				return pets_equipmentset;
			}
		}

		return NewEntity();
	}

	static PetsEquipmentset FindOne(
		Database& db,
		int pets_equipmentset_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {} = {} LIMIT 1",
				BaseSelect(),
				PrimaryKey(),
				pets_equipmentset_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			PetsEquipmentset e{};

			e.set_id     = row[0] ? static_cast<int32_t>(atoi(row[0])) : 0;
			e.setname    = row[1] ? row[1] : "";
			e.nested_set = row[2] ? static_cast<int32_t>(atoi(row[2])) : -1;

			return e;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int pets_equipmentset_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				pets_equipmentset_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		const PetsEquipmentset &e
	)
	{
		std::vector<std::string> v;

		auto columns = Columns();

		v.push_back(columns[0] + " = " + std::to_string(e.set_id));
		v.push_back(columns[1] + " = '" + Strings::Escape(e.setname) + "'");
		v.push_back(columns[2] + " = " + std::to_string(e.nested_set));

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", v),
				PrimaryKey(),
				e.set_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static PetsEquipmentset InsertOne(
		Database& db,
		PetsEquipmentset e
	)
	{
		std::vector<std::string> v;

		v.push_back(std::to_string(e.set_id));
		v.push_back("'" + Strings::Escape(e.setname) + "'");
		v.push_back(std::to_string(e.nested_set));

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", v)
			)
		);

		if (results.Success()) {
			e.set_id = results.LastInsertedID();
			return e;
		}

		e = NewEntity();

		return e;
	}

	static int InsertMany(
		Database& db,
		const std::vector<PetsEquipmentset> &entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &e: entries) {
			std::vector<std::string> v;

			v.push_back(std::to_string(e.set_id));
			v.push_back("'" + Strings::Escape(e.setname) + "'");
			v.push_back(std::to_string(e.nested_set));

			insert_chunks.push_back("(" + Strings::Implode(",", v) + ")");
		}

		std::vector<std::string> v;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				Strings::Implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<PetsEquipmentset> All(Database& db)
	{
		std::vector<PetsEquipmentset> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			PetsEquipmentset e{};

			e.set_id     = row[0] ? static_cast<int32_t>(atoi(row[0])) : 0;
			e.setname    = row[1] ? row[1] : "";
			e.nested_set = row[2] ? static_cast<int32_t>(atoi(row[2])) : -1;

			all_entries.push_back(e);
		}

		return all_entries;
	}

	static std::vector<PetsEquipmentset> GetWhere(Database& db, const std::string &where_filter)
	{
		std::vector<PetsEquipmentset> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			PetsEquipmentset e{};

			e.set_id     = row[0] ? static_cast<int32_t>(atoi(row[0])) : 0;
			e.setname    = row[1] ? row[1] : "";
			e.nested_set = row[2] ? static_cast<int32_t>(atoi(row[2])) : -1;

			all_entries.push_back(e);
		}

		return all_entries;
	}

	static int DeleteWhere(Database& db, const std::string &where_filter)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int Truncate(Database& db)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"TRUNCATE TABLE {}",
				TableName()
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int64 GetMaxId(Database& db)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"SELECT COALESCE(MAX({}), 0) FROM {}",
				PrimaryKey(),
				TableName()
			)
		);

		return (results.Success() && results.begin()[0] ? strtoll(results.begin()[0], nullptr, 10) : 0);
	}

	static int64 Count(Database& db, const std::string &where_filter = "")
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"SELECT COUNT(*) FROM {} {}",
				TableName(),
				(where_filter.empty() ? "" : "WHERE " + where_filter)
			)
		);

		return (results.Success() && results.begin()[0] ? strtoll(results.begin()[0], nullptr, 10) : 0);
	}

	static std::string BaseReplace()
	{
		return fmt::format(
			"REPLACE INTO {} ({}) ",
			TableName(),
			ColumnsRaw()
		);
	}

	static int ReplaceOne(
		Database& db,
		const PetsEquipmentset &e
	)
	{
		std::vector<std::string> v;

		v.push_back(std::to_string(e.set_id));
		v.push_back("'" + Strings::Escape(e.setname) + "'");
		v.push_back(std::to_string(e.nested_set));

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseReplace(),
				Strings::Implode(",", v)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int ReplaceMany(
		Database& db,
		const std::vector<PetsEquipmentset> &entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &e: entries) {
			std::vector<std::string> v;

			v.push_back(std::to_string(e.set_id));
			v.push_back("'" + Strings::Escape(e.setname) + "'");
			v.push_back(std::to_string(e.nested_set));

			insert_chunks.push_back("(" + Strings::Implode(",", v) + ")");
		}

		std::vector<std::string> v;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseReplace(),
				Strings::Implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}
};

#endif //EQEMU_BASE_PETS_EQUIPMENTSET_REPOSITORY_H
