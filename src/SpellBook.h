#pragma once

class SpellBook;

class SpellIcon : public InterfaceElem
{
private:
	sf::Sprite sprite;
	SpellBook& owner;
	void clickLeft(bool down, bool previousState) override;
	void clickRight(bool down, bool previousState) override;

public:
	SpellIcon(SpellBook& book, const sf::Vector2f pos, Spell type) :
		owner(book),
		type(type)
	{
		this->shape = sf::FloatRect(pos, { 83, 65 });
		this->sprite.setTexture(*graphics.allSpellIcons);
		this->sprite.setTextureRect(Graphics::selectSpellIcon(type));
		this->sprite.setPosition(pos);
	}
	void render(sf::RenderTarget* target)
	{
		target->draw(sprite);
	}
	Spell type;
};

class SpellBook :
	public WindowObject
{
public:
	SpellBook(Spell& selectedSpell);
	~SpellBook();
	Spell& spellToCast;
	std::list<std::shared_ptr<SpellIcon>> spellIcons;

	void render(sf::RenderTarget* target) override;
};
