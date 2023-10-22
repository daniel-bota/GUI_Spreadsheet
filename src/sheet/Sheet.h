#pragma once
#include "Cell/Cell.h"
#include "Coordinates/Address.h"
#include <vector>
#include <map>
#include <memory>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <stdexcept>
#include <ranges>
#include <nlohmann/json.hpp>

class Sheet : std::enable_shared_from_this<Sheet>
{
public:
	Sheet() = default;

	const std::map<Address, std::shared_ptr<Cell>>& Values() const { return values; }

	void Initialize(const std::map<Address, std::shared_ptr<Cell>>& importedValues = {});

	void AddCell(std::shared_ptr<Cell> cell);
    void AddCell(const Address& address, const std::string& input);

    Address CellTitleToAddress(const std::string& title);
    int ColTitleToIndex(const std::string& colTitle);

	nlohmann::json Serialize();
	bool Deserialize(const nlohmann::json& source);
private:
	std::map<Address, std::shared_ptr<Cell>> values{};

	std::map<Address, std::vector<Address>> referencing{};
};

