//Cell.h
#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button/Button.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace Gameplay
{
	enum class CellState
	{
		HIDDEN,
		OPEN,
		FLAGGED,
	};

	enum class CellType
	{
		EMPTY,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		MINE,
	};

	class Board;

	class Cell
	{
	private:
		sf::Vector2i position;

		const int tile_size = 128;
		const int slice_count = 12;

		const float cell_top_offset = 274.0f;
		const float cell_left_offset = 586.0f;

		const std::string cell_texture_path = "assets/textures/cells.jpeg";

		Button* cell_button;

		CellState current_cell_state;
		CellType cell_type;

		Board* board;

		void initialize(float width, float height, sf::Vector2i position, Board* board);

		void registerCellButtonCallback();
		void cellButtonCallback(MouseButtonType button_type);


	public:
		Cell(float width, float height, sf::Vector2i position, Board* board);
		~Cell() = default;

		CellState getCellState() const;
		void setCellState(CellState state);
		CellType getCellType() const;
		void setCellType(CellType type);

		void setCellTexture();

		sf::Vector2f getCellScreenPosition(int width, int height) const;
		sf::Vector2i getCellPoisition();

		bool canOpenCell() const;
		void open();

		void toggleFlag();

		void update(Event::EventPollingManager& event_manager, sf::RenderWindow& window);

		void render(sf::RenderWindow& window);
	};
}