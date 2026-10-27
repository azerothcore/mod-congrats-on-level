SET @ENTRY:=60000;
DELETE FROM `acore_string` WHERE `entry` = @ENTRY+0;
INSERT INTO `acore_string` (`entry`, `content_default`) VALUES
(@ENTRY+0, 'This server is running the |cff4CFF00CongratsOnLevel |rmodule.');

DELETE FROM `acore_string_locale` WHERE `entry` = @ENTRY+0 AND `locale` IN ('esES', 'esMX');
INSERT INTO `acore_string_locale` (`entry`, `locale`, `content`) VALUES
(@ENTRY+0, 'esES', 'Este servidor está ejecutando el módulo |cff4CFF00CongratsOnLevel|r'),
(@ENTRY+0, 'esMX', 'Este servidor está ejecutando el módulo |cff4CFF00CongratsOnLevel|r');
