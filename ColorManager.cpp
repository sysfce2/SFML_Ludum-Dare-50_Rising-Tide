#include "ColorManager.h"

#include <vector>

namespace {
	std::vector<sf::Color> palette;
	std::vector<sf::Color> desiredPalette;
	sf::Image paletteSheet;
	int currentPalette = 0;
}

void cm::init() {
	paletteSheet.loadFromFile("Resource/Image/Palettes.png");
	palette.resize(paletteSheet.getSize().x);
	desiredPalette.resize(paletteSheet.getSize().x);

	selectPalette(0, true);
}

void cm::selectPalette(int index, bool instant) {
	if (index < 0) {
		index = 0;
	}
	while (index >= paletteSheet.getSize().y) {
		index -= paletteSheet.getSize().y;
	}
	currentPalette = index;

	for (int i = 0; i < desiredPalette.size(); i++) {
		desiredPalette[i] = paletteSheet.getPixel(i, index);
	}

	if (instant) {
		palette = desiredPalette;
	}
}

int cm::getCurrentPalette() {
	return currentPalette;
}

void cm::updatePalette(sf::Time elapsed) {
	for (int i = 0; i < palette.size(); i++) {
		palette[i] = adjustColor(palette[i], desiredPalette[i], elapsed.asSeconds() * 200);
	}
}

sf::Color cm::getPaletteColor(int index) {
	if (index >= 0 && index < palette.size()) {
		return palette[index];
	}
	else if (!palette.empty()) {
		return palette[0];
	}
	return sf::Color();
}

sf::Color cm::getSkyColor() {
	return getPaletteColor(6);
}

sf::Color cm::getWaterColor() {
	return getPaletteColor(14);
}

sf::Color cm::getTextColor() {
	return getPaletteColor(0);
}

sf::Color cm::adjustColor(sf::Color input, sf::Color desired, float amount) {
	float r = adjustComponent(input.r, desired.r, amount);
	float g = adjustComponent(input.g, desired.g, amount);
	float b = adjustComponent(input.b, desired.b, amount);
	return sf::Color(r, g, b);
}

float cm::adjustComponent(float input, float desired, float amount) {
	if (input < desired) {
		input += amount;
		if (input > desired) {
			input = desired;
		}
	}
	else if (input > desired) {
		input -= amount;
		if (input < desired) {
			input = desired;
		}
	}
	return input;
}
