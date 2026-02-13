//Board.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"


namespace Gameplay 
{
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

		// Randomization
		std::default_random_engine randomEngine;
		std::random_device randomDevice;

		// Number of mines
		static const int minesCount = 9;

		const std::string boardTexturePath = "Assets/textures/board.png";

		sf::Texture boardTexture;
		sf::Sprite boardSprite;

		Cell* cell[numberOfRows] [numberOfColumns];

		void initialize();
		void initializeBoardImage();

		void createBoard();

		float getCellWidthInBoard() const;
		float getCellHeightInBoard() const;

		// Populating the Board
		void populatedBoard();
		void populatedMines();

		void initializeVariables();

	public:
		Board();

		void render(sf::RenderWindow& window);

	};
}