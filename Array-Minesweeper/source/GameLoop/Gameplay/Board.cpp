//Board.cpp
#include "../../../header/GameLoop/Gameplay/Board.h"

namespace Gameplay
{
	Board::Board()
	{
		initialize();
	}

	void Board::initialize()
	{
		initializeBoardImage();
		initializeVariables();
		createBoard();
		// Populate the board
		populatedBoard();
	}

	void Board::initializeBoardImage()
	{
		if (!boardTexture.loadFromFile(boardTexturePath))
		{
			std::cerr << "failed to load board texture!" << std::endl;
			return;
		}

		boardSprite.setTexture(boardTexture);
		boardSprite.setPosition(boardPosition, 0);
		boardSprite.setScale(boardWidth / boardTexture.getSize().x, boardHeight / boardTexture.getSize().y);
	}

	void Board::initializeVariables()
	{
		randomEngine.seed(randomDevice());   //Function to initialize random engine
	}


	float Board::getCellWidthInBoard() const
	{
		return (boardWidth - horizontalCellPadding) / numberOfColumns;
	}

	float Board::getCellHeightInBoard() const
	{
		return (boardHeight - verticalCellPadding) / numberOfRows;
	}

	void Board::createBoard()
	{
		float cell_width = getCellWidthInBoard();
		float cell_height = getCellHeightInBoard();
		for (int row= 0; row < numberOfRows; row++)
		{
			for (int col = 0; col < numberOfColumns; col++)
			{
				cell[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col), this); 
			}
		}
	}

	void Board::populatedBoard()
	{
		populatedMines();
		populateCells();
	}

	void Board::populatedMines()
	{
		std::uniform_int_distribution<int> x_dist(0, numberOfColumns - 1);
		std::uniform_int_distribution<int> y_dist(0, numberOfRows - 1);

		int mines_placed = 0;

		while (mines_placed <minesCount)
		{
			int x = x_dist(randomEngine);
			int y = y_dist(randomEngine);

			if (cell[x][y]->getCellType() != CellType::MINE)
			{
				cell[x][y]->setCellType(CellType::MINE);
				++mines_placed;
			}
		}
	}

	int Board::countMinesAround(sf::Vector2i cell_position)
	{
		int mine_around = 0;

		for (int a = -1; a <= 1; a++)
		{
			for (int b = -1; b <= 1; b++)
			{
				// Validate cell's position and check current cell
				if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
					continue;

				// Check mines
				if (cell[cell_position.x + a][cell_position.y + b]->getCellType() == CellType::MINE)
				{
					mine_around++;
				}
			}
		}

		return mine_around;
	}

	bool Board::isValidCellPosition(sf::Vector2i cell_positon) {
		return (cell_positon.x >= 0 && cell_positon.y >= 0 && cell_positon.x < numberOfColumns && cell_positon.y < numberOfRows);
	}

	void Board::populateCells()
	{

		for (int row = 0; row < numberOfRows; row++)
		{
			for (int col = 0; col < numberOfColumns; col++)
			{
				if (cell[row][col]->getCellType() != CellType::MINE)
				{
					int mines_around = countMinesAround(sf::Vector2i(row, col));

					cell[row][col]->setCellType(static_cast<CellType>(mines_around));
				}
			}
		}
	}

	void Board::onCellButtonClick(sf::Vector2i cell_position, MouseButtonType mouse_button_type)
	{
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			openCell(cell_position);
		}
		else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			toggleFlag(cell_position);
		}
	}

	void Board::openCell(sf::Vector2i cell_position)
	{
		if (!cell[cell_position.x][cell_position.y]->canOpenCell())
		{
			return;
		}
		processCellType(cell_position);
	}

	void Board::toggleFlag(sf::Vector2i cell_position)
	{
		cell[cell_position.x][cell_position.y]->toggleFlag();
		flaggedCells += (cell[cell_position.x][cell_position.y]->getCellState() == CellState::FLAGGED) ? 1 : -1;
	}


	void Board::processCellType(sf::Vector2i cell_position)
	{
		switch (cell[cell_position.x][cell_position.y]->getCellType())
		{
		case CellType::EMPTY:
			processEmptyCell(cell_position);
			break;
		case CellType::MINE:
			break;
		default:
			cell[cell_position.x][cell_position.y]->open();
			break;
		}
	}

	void Board::processEmptyCell(sf::Vector2i cell_position)
	{
		CellState current_state = cell[cell_position.x][cell_position.y]->getCellState();

		switch (current_state)
		{
		case Gameplay::CellState::OPEN:
			return;
		default:
			cell[cell_position.x][cell_position.y]->open();
		}


		for (int a = -1; a <= 1; a++)
		{
			for (int b = -1; b <= 1; b++)
			{
				sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);

				if ((a == 0 && b == 0) || !isValidCellPosition(next_cell_position))
				{
					continue;
				}

				CellState next_cell_state = cell[next_cell_position.x][next_cell_position.y]->getCellState();

				if (next_cell_state == CellState::FLAGGED)
				{
					toggleFlag(next_cell_position);
				}

				openCell(next_cell_position);
			}
		}
	}


	void Board::update(Event::EventPollingManager& event_manager, sf::RenderWindow& window)
	{
		for (int row = 0; row < numberOfRows; row++)
		{
			for (int col = 0; col < numberOfColumns; col++)
			{
				cell[row][col]->update(event_manager, window);
			}
		}
	}

	void Board::render(sf::RenderWindow& window)
	{
		window.draw(boardSprite);

		for (int row= 0; row < numberOfRows; row++)
		{
			for (int col = 0; col < numberOfColumns; col++)
			{
				cell[row][col]->render(window);
			}
		}
		
	}
}