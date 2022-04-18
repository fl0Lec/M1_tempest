
#include "chooselevelscene.hpp"

#include "button.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "game.hpp"
#include "gamescene.hpp"
#include "levelbutton.hpp"
#include "levelrenderer.hpp"
#include "player.hpp"
#include "textcomponent.hpp"
#include "vect2.hpp"

using namespace Engine;

ChooseLevelScene::ChooseLevelScene(unsigned int playerId)
{
    m_objects.emplace_back(std::shared_ptr<TextComponent>{
        new TextComponent{
            Game::instance()->center() - Vect2f{0, Game::instance()->height() / 4.0f},
            "Player " + std::to_string(playerId)
        }
    });
    m_objects.emplace_back(std::shared_ptr<TextComponent>{
        new TextComponent{
            Game::instance()->center() - Vect2f{0, Game::instance()->height() / 10.0f},
            "Choose your level"
        }
    });

    const std::vector<LevelType> levels{
        LevelType::PLUS, LevelType::SQUARE, LevelType::TRIANGLE,
        LevelType::CIRCLE
    };

    const size_t baseY = 3 * Game::instance()->height() / 4;
    const size_t margin = 60;
    const size_t width = (Game::instance()->width() - ((levels.size() + 1) * margin))
        / levels.size();

    size_t currentX = margin;
    for(const auto& type : levels)
    {
        addButton(std::shared_ptr<LevelButton>{
            new LevelButton{Vect2f{(float) currentX, baseY - width/2.0f},
                Vect2f{(float) width}, type, [=](auto){
                    Game::instance()->setCurrentScene(
                        std::shared_ptr<GameScene>{new GameScene{type}}
                    );
                }
            }
        });

        currentX += width + margin;
    }
}
