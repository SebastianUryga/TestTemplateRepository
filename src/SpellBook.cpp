#include "GuiHandler.h"

SpellBook::SpellBook(Spell& selectedSpell)
	:WindowObject(400,200,700,400,GH.globalFont), spellToCast(selectedSpell)
{
	for (size_t i = 0; i < allSpells.size(); i++)
	{
		auto pos = this->background.getPosition();
		pos += sf::Vector2f{ 20.f + (i % 7) * 90,10.f + (i / 7) * 70 };
		auto temp = std::make_shared<SpellIcon>(*this, pos, allSpells[i]);
		this->spellIcons.push_back(temp);
		this->interactiveElem.push_back(this->spellIcons.back());
	}
	this->buttons["OK"] = std::make_shared<Button>(
		400+620, 200+350, 60, 30, &this->font, "OK"
		);
	this->buttons["OK"]->addFuctionallity([=]() {
		close();
	});
	this->interactiveElem.push_back(buttons["OK"]);
}

SpellBook::~SpellBook() {}

void SpellBook::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	for (auto item : this->spellIcons)
	{
		item->render(target);
	}
}

void SpellIcon::clickLeft(bool down, bool previousState)
{
	if (down == false && previousState)
	{
		owner.spellToCast = this->type;
		owner.close();
	}
}

void SpellIcon::clickRight(bool down, bool previousState)
{
	if (down  && previousState == false)
	{
		auto pop = std::make_shared<WindowObject>(
			GH.mousePosWindow.x, GH.mousePosWindow.y,150,100,GH.globalFont);
		pop->addText(spellToString[this->type.spell], sf::Vector2f(20, 20));
		GH.makePopup(pop);
	}
}
