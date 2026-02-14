//Board.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"


namespace Gameplay 
{
	class GameplayManager;

	enum class BoardState
	{
		FIRST_CELL,
		PLAYING,
		COMPLETE,
	};

	class Board 
	{
	private:
		const float boardWidth = 866.0f;
		const float boardHeight = 1080.0f;
		const float boardPosition = 530.0f;

		static const int numberOfRows = 9;
		static const int numberOfColumns = 9;

		const float horizontalCellPadding = 115.0f;
		const float verticalCellPadding = 329.0f;

		BoardState boardState;

		// Randomization
		std::default_random_engine randomEngine;
		std::random_device randomDevice;

		// Number of mines
		static const int minesCount = 9;

		int flaggedCells;

		const std::string boardTexturePath = "Assets/textures/board.png";

		sf::Texture boardTexture;
		sf::Sprite boardSprite;

		Cell* cell[numberOfRows] [numberOfColumns];

		GameplayManager* gameplay_manager;

		void initialize(GameplayManager* gameplayManager);
		void initializeBoardImage();
		void initializeVariables(GameplayManager* gameplayManager);

		void createBoard();

		float getCellWidthInBoard() const;
		float getCellHeightInBoard() const;

		// Populating the Board
		void populatedBoard(sf::Vector2i cell_position);
		void populatedMines(sf::Vector2i first_cell_position);

		int countMinesAround(sf::Vector2i cell_position);
		void populateCells();
		bool isValidCellPosition(sf::Vector2i cell_poision);

		void openCell(sf::Vector2i cell_poisition);

		void toggleFlag(sf::Vector2i cell_poisition);

		void processCellType(sf::Vector2i cell_position);
		void processEmptyCell(sf::Vector2i cell_position);

		void processMineCell(sf::Vector2i cell_position);

		bool isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y);

	public:
		Board(GameplayManager* gameplayManager);

		void onCellButtonClick(sf::Vector2i cell_position, MouseButtonType mouse_button_type);
		void revealAllMines();

		BoardState getBoardStat() const;
		void setBoardState(BoardState state);

		void update(Event::EventPollingManager& event_manager, sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

	};
}