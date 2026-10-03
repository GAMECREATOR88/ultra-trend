#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Trend {
    std::string label;
    std::string category;
    int score;
    int delta;
    std::string summary;
};

static std::vector<Trend> makeTrends() {
    return {
        {"AI creators", "Social", 96, 18, "Creators are posting short-form AI workflows and tutorials."},
        {"Smart wearables", "Tech", 88, 14, "People are tracking productivity and wellness data in real time."},
        {"Minimal living", "Lifestyle", 82, 12, "Searches are up for calm routines and clutter-free homes."},
        {"Streetwear drops", "Culture", 91, 16, "Fashion communities are reacting quickly to capsule drops."},
        {"Eco travel", "Lifestyle", 79, 11, "Travel demand is shifting toward lighter, lower-impact plans."},
        {"Creators economy", "Business", 93, 20, "Audience-first businesses are outperforming broad-brand noise."},
    };
}

static sf::Color blend(sf::Color a, sf::Color b, float t) {
    return sf::Color(
        static_cast<sf::Uint8>(a.r + (b.r - a.r) * t),
        static_cast<sf::Uint8>(a.g + (b.g - a.g) * t),
        static_cast<sf::Uint8>(a.b + (b.b - a.b) * t),
        static_cast<sf::Uint8>(a.a + (b.a - a.a) * t));
}

static sf::Font loadFont() {
    sf::Font font;
    const std::vector<std::string> paths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Bold.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf"
    };

    for (const auto& path : paths) {
        if (font.loadFromFile(path)) {
            return font;
        }
    }

    return sf::Font();
}

static void drawTrendCard(sf::RenderWindow& window,
                         const Trend& trend,
                         const sf::Font& font,
                         float time,
                         float x,
                         float y,
                         bool selected,
                         int index) {
    const float alpha = selected ? 255.0f : 230.0f;
    sf::RectangleShape card(sf::Vector2f(290.0f, 170.0f));
    card.setPosition(x, y);
    card.setFillColor(selected ? sf::Color(255, 255, 255, 230) : sf::Color(25, 25, 25, 220));
    card.setOutlineColor(selected ? sf::Color(200, 200, 200, 250) : sf::Color(90, 90, 90, 180));
    card.setOutlineThickness(1.5f);
    window.draw(card);

    float glow = 0.5f + 0.5f * std::sin(time * 2.0f + index);
    sf::RectangleShape glowBar(sf::Vector2f(220.0f, 8.0f));
    glowBar.setPosition(x + 22.0f, y + 110.0f);
    glowBar.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(150 + glow * 60)));
    window.draw(glowBar);

    sf::Text label(trend.label, font, 22U);
    label.setFillColor(selected ? sf::Color::Black : sf::Color::White);
    label.setPosition(x + 22.0f, y + 18.0f);
    window.draw(label);

    sf::Text category(trend.category, font, 12U);
    category.setFillColor(selected ? sf::Color(48, 48, 48) : sf::Color(196, 196, 196));
    category.setPosition(x + 22.0f, y + 54.0f);
    window.draw(category);

    sf::Text score(std::to_string(trend.score), font, 38U);
    score.setFillColor(selected ? sf::Color::Black : sf::Color::White);
    score.setPosition(x + 210.0f, y + 16.0f);
    window.draw(score);

    sf::Text delta((trend.delta > 0 ? "+" : "") + std::to_string(trend.delta) + "%", font, 13U);
    delta.setFillColor(trend.delta > 0 ? sf::Color(255, 255, 255) : sf::Color(180, 180, 180));
    delta.setPosition(x + 218.0f, y + 64.0f);
    window.draw(delta);

    sf::VertexArray line(sf::LinesStrip, 8);
    for (int i = 0; i < 8; ++i) {
        float px = x + 24.0f + i * 25.0f;
        float py = y + 138.0f - std::sin(time * 3.0f + i + index) * 12.0f - (i % 2) * 4.0f;
        line[i].position = sf::Vector2f(px, py);
        line[i].color = selected ? sf::Color(42, 42, 42, 180) : sf::Color(255, 255, 255, 160);
    }
    window.draw(line);
}

int main() {
    const int width = 1280;
    const int height = 860;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ultra Trend", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Font font = loadFont();
    if (font.getInfo().family.empty()) {
        std::cout << "No system font found; using SFML defaults where available.\n";
    }

    auto trends = makeTrends();
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        const float time = clock.getElapsedTime().asSeconds();

        window.clear(sf::Color(10, 10, 10));

        for (int i = 0; i < 10; ++i) {
            sf::CircleShape orb(14.0f + i * 2.0f);
            orb.setFillColor(sf::Color(255, 255, 255, 12 + i * 2));
            orb.setPosition(80.0f + i * 120.0f + std::sin(time * 0.8f + i) * 22.0f,
                             120.0f + std::cos(time * 1.2f + i) * 22.0f);
            window.draw(orb);
        }

        sf::Text title("ULTRA TREND", font, 40U);
        title.setFillColor(sf::Color::White);
        title.setPosition(80.0f, 48.0f);
        window.draw(title);

        sf::Text subtitle("AI DAILY PULSE", font, 14U);
        subtitle.setFillColor(sf::Color(180, 180, 180));
        subtitle.setPosition(82.0f, 100.0f);
        window.draw(subtitle);

        sf::RectangleShape topBar(sf::Vector2f(940.0f, 140.0f));
        topBar.setPosition(80.0f, 132.0f);
        topBar.setFillColor(sf::Color(240, 240, 240, 8));
        topBar.setOutlineColor(sf::Color(255, 255, 255, 24));
        topBar.setOutlineThickness(1.0f);
        window.draw(topBar);

        sf::Text heading("What people are searching and doing", font, 30U);
        heading.setFillColor(sf::Color::White);
        heading.setPosition(118.0f, 170.0f);
        window.draw(heading);

        sf::Text summary("The strongest signals today are AI tools, creator-first brands, and calm minimal routines.", font, 18U);
        summary.setFillColor(sf::Color(200, 200, 200));
        summary.setPosition(118.0f, 215.0f);
        window.draw(summary);

        sf::RectangleShape insight(sf::Vector2f(360.0f, 600.0f));
        insight.setPosition(1040.0f, 120.0f);
        insight.setFillColor(sf::Color(245, 245, 245, 10));
        insight.setOutlineColor(sf::Color(255, 255, 255, 26));
        insight.setOutlineThickness(1.2f);
        window.draw(insight);

        sf::Text insightTitle("INSIGHT", font, 18U);
        insightTitle.setFillColor(sf::Color::White);
        insightTitle.setPosition(1072.0f, 150.0f);
        window.draw(insightTitle);

        sf::Text insightHeadline("Trend 01", font, 30U);
        insightHeadline.setFillColor(sf::Color::White);
        insightHeadline.setPosition(1072.0f, 188.0f);
        window.draw(insightHeadline);

        sf::Text insightBody("AI tools are hitting the mainstream as people want faster workflows, smarter automations, and clearer creative systems.", font, 17U);
        insightBody.setFillColor(sf::Color(220, 220, 220));
        insightBody.setPosition(1072.0f, 238.0f);
        insightBody.setString("AI tools are hitting the mainstream as people want faster workflows, smarter automations, and clearer creative systems.");
        window.draw(insightBody);

        sf::Text statText("92% avg confidence", font, 15U);
        statText.setFillColor(sf::Color::White);
        statText.setPosition(1072.0f, 610.0f);
        window.draw(statText);

        sf::RectangleShape statBar(sf::Vector2f(240.0f, 10.0f));
        statBar.setPosition(1072.0f, 642.0f);
        statBar.setFillColor(sf::Color(255, 255, 255, 12));
        window.draw(statBar);

        sf::RectangleShape statBarFill(sf::Vector2f(220.0f, 10.0f));
        statBarFill.setPosition(1072.0f, 642.0f);
        statBarFill.setFillColor(sf::Color::White);
        window.draw(statBarFill);

        int x = 80;
        int y = 300;
        for (size_t i = 0; i < trends.size(); ++i) {
            bool selected = i == 0;
            drawTrendCard(window, trends[i], font, time, static_cast<float>(x), static_cast<float>(y), selected, static_cast<int>(i));
            x += 310;
            if ((i + 1) % 3 == 0) {
                x = 80;
                y += 200;
            }
        }

        sf::Text footer("daily trend signal • momentum index • black & white mode", font, 13U);
        footer.setFillColor(sf::Color(180, 180, 180));
        footer.setPosition(80.0f, 800.0f);
        window.draw(footer);

        window.display();
    }

    return 0;
}

