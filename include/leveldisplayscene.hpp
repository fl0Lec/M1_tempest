/**
 * @file leveldisplayscene.hpp
 * @brief Scene to display all levels
 */

#ifndef __LEVELDISPLAYSCENE_H__
#define __LEVELDISPLAYSCENE_H__

#include "scene.hpp"

#include <vector>

#include "levelrenderer.hpp"

class LevelDisplayScene
    : public Engine::Scene
{
public:
    LevelDisplayScene();

    virtual void update(const Engine::Input &in) override;
    virtual void render(const Engine::Output &out) const override;

private:
    std::vector<LevelRenderer> m_levels;
    size_t m_currentLevel;

};

#endif
