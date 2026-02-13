//Cell.cpp
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/GameLoop/Gameplay/Board.h"

namespace Gameplay
{
	Cell::Cell(float width, float height, sf::Vector2i position, Board* board)
	{
		initialize(width, height, position, board);
	}

	void Cell::initialize(float width, float height, sf::Vector2i position, Board* board)
	{
		this->position = position;
		this->board = board;
		sf::Vector2f cellScreenPosition = getCellScreenPosition(width, height);
		cell_button = new Button(cell_texture_path, cellScreenPosition, width * slice_count, height);
		current_cell_state = CellState::HIDDEN;

		// Register a method
		registerCellButtonCallback();
	}

	CellState Cell::getCellState() const { return current_cell_state; }

	void Cell::setCellState(CellState state) { current_cell_state = state; }

	CellType Cell::getCellType() const { return cell_type; }

	void Cell::setCellType(CellType type) { cell_type = type; }

	sf::Vector2i Cell::getCellPoisition() { return position; }

	void Cell::setCellTexture()
	{
		int index = static_cast<int>(cell_type);

		switch (current_cell_state)
		{
		case CellState::OPEN:
			cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
			break;
		case CellState::HIDDEN:
			cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
			break;
		case CellState::FLAGGED:
			cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
			break;
		}
	}

	sf::Vector2f Cell::getCellScreenPosition(int width, int heigh) const
	{
		float xScreenPosition = cell_left_offset +  position.x * width;
		float yScreenPosition = cell_top_offset +position.y * heigh;
		return sf::Vector2f(xScreenPosition, yScreenPosition);
	}

	void Cell::registerCellButtonCallback()
	{
		cell_button->registerCallbackFunction([this](MouseButtonType button_type)
		{
			cellButtonCallback(button_type);
		});
	}

	void Cell::cellButtonCallback(MouseButtonType button_type)
	{
		board->onCellButtonClick(getCellPoisition(), button_type);
	}

	void Cell::update(Event::EventPollingManager& event_manager, sf::RenderWindow& window)
	{
		if (cell_button)
			cell_button->handleButtonInteractions(event_manager, window);
	}


	void Cell::render(sf::RenderWindow& window)
	{
		// Set cell's texture
		setCellTexture();

		// render the cell button
		if (cell_button) cell_button->render(window);
	}
}