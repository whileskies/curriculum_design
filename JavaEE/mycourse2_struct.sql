/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80011
 Source Host           : localhost:3306
 Source Schema         : mycourse2

 Target Server Type    : MySQL
 Target Server Version : 80011
 File Encoding         : 65001

 Date: 04/07/2020 22:51:41
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course`  (
  `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '课程id 自动增长',
  `code` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '课程邀请码 唯一',
  `name` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '课程名称 默认为空',
  `create_time` datetime(0) NULL DEFAULT NULL COMMENT '课程创建时间',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `unique_course_code`(`code`) USING BTREE COMMENT '课程邀请码 唯一索引'
) ENGINE = InnoDB AUTO_INCREMENT = 38 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for course_student
-- ----------------------------
DROP TABLE IF EXISTS `course_student`;
CREATE TABLE `course_student`  (
  `course_id` int(6) UNSIGNED NOT NULL COMMENT '课程id',
  `user_id` int(6) UNSIGNED NOT NULL COMMENT '学生（用户）id',
  `enter_time` datetime(0) NOT NULL COMMENT '加入时间',
  PRIMARY KEY (`course_id`, `user_id`) USING BTREE,
  INDEX `student_id`(`user_id`) USING BTREE,
  CONSTRAINT `course_student_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `course_student_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for course_teacher
-- ----------------------------
DROP TABLE IF EXISTS `course_teacher`;
CREATE TABLE `course_teacher`  (
  `course_id` int(6) UNSIGNED NOT NULL COMMENT '课程Id',
  `user_id` int(6) UNSIGNED NOT NULL COMMENT '教师（用户）id',
  PRIMARY KEY (`course_id`, `user_id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE,
  CONSTRAINT `course_teacher_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `course_teacher_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for notice
-- ----------------------------
DROP TABLE IF EXISTS `notice`;
CREATE TABLE `notice`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '公告id 自动增长',
  `course_id` int(6) UNSIGNED NOT NULL COMMENT '课程id 外键',
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '公告标题 默认为‘’',
  `content` varchar(10000) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '公告内容 默认为\'\'',
  `writer_id` int(6) UNSIGNED NOT NULL COMMENT '公告书写写 用户id 外键',
  `create_time` datetime(0) NOT NULL ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '公告发布日期',
  `update_time` datetime(0) NOT NULL COMMENT '公告更新时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `notice_ibfk_1`(`writer_id`) USING BTREE,
  CONSTRAINT `notice_ibfk_1` FOREIGN KEY (`writer_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `notice_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `course` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 25 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for resource
-- ----------------------------
DROP TABLE IF EXISTS `resource`;
CREATE TABLE `resource`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '资源id',
  `course_id` int(10) NOT NULL COMMENT '课程id',
  `file_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '文件名',
  `file_path` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '文件保存路径',
  `upload_time` datetime(0) NOT NULL COMMENT '上传时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE COMMENT '课程id索引'
) ENGINE = InnoDB AUTO_INCREMENT = 45 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for task
-- ----------------------------
DROP TABLE IF EXISTS `task`;
CREATE TABLE `task`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '作业id 自动增长',
  `course_id` int(6) UNSIGNED NOT NULL COMMENT '课程id',
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '作业标题 默认为\'\'',
  `content` varchar(10000) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '作业内容 默认为\'\'',
  `deadline` datetime(0) NULL DEFAULT NULL COMMENT '作业截止日期',
  `writer_id` int(6) UNSIGNED NOT NULL COMMENT '作业布置者 用户id 外键',
  `create_time` datetime(0) NOT NULL COMMENT '作业布置日期',
  `update_time` datetime(0) NOT NULL COMMENT '更新时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `task_writer`(`writer_id`) USING BTREE,
  CONSTRAINT `task_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `task_ibfk_2` FOREIGN KEY (`writer_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 22 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for task_file
-- ----------------------------
DROP TABLE IF EXISTS `task_file`;
CREATE TABLE `task_file`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '作业',
  `task_id` int(10) NOT NULL COMMENT '作业id',
  `user_id` int(10) NOT NULL COMMENT '学生id',
  `upload_time` datetime(0) NOT NULL COMMENT '作业提交时间',
  `file_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '文件名',
  `file_path` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '文件路径',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `task_id`(`task_id`) USING BTREE COMMENT '作业号索引'
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '用户姓名 自动增长',
  `email` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户邮箱',
  `password` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户密码',
  `role` char(1) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 's' COMMENT '用户角色 s-学生 t-教师 a-管理员 默认为s',
  `name` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户名字 默认为\'\'',
  `school_id` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户学号/教工号 默认为\'\'',
  `school` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户学校 默认为\'\'',
  `dept` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户院系 默认为\'\'',
  `major` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户专业 默认为\'\'',
  `class` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户班级 默认为\'\'',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `unique_user_email`(`email`) USING BTREE COMMENT '邮箱的唯一索引'
) ENGINE = InnoDB AUTO_INCREMENT = 31 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
