CREATE TABLE IF NOT EXISTS `mod_congrats_on_level_items` (
    `level` tinyint unsigned NOT NULL DEFAULT 0,
    `money` int unsigned NOT NULL DEFAULT 0,
    `spell` int unsigned NOT NULL DEFAULT 0,
    `learn` boolean NOT NULL DEFAULT false,
    `itemId1` int unsigned NOT NULL DEFAULT 0,
    `itemId2` int unsigned NOT NULL DEFAULT 0,
    `race` tinyint unsigned NOT NULL DEFAULT 0,
    `class` tinyint unsigned NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `mod_congrats_on_level_items`;
INSERT INTO `mod_congrats_on_level_items` (`level`, `money`, `spell`, `learn`, `itemId1`, `itemId2`, `race`, `class`) VALUES
(10, 1, 20217, 0, 3419, 45063, 0, 0),
(20, 10, 48161, 0, 5433, 38578, 0, 0),
(30, 15, 48469, 0, 18231, 46780, 0, 0),
(40, 20, 20217, 0, 31945, 49704, 0, 0),
(50, 25, 48161, 0, 11382, 32542, 0, 0),
(60, 30, 48469, 0, 37863, 33219, 0, 0),
(70, 35, 48161, 0, 9360, 54212, 0, 0),
(80, 100, 20217, 0, 9361, 40110, 0, 0);
