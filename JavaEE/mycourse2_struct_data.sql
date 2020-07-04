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

 Date: 04/07/2020 22:51:58
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
-- Records of course
-- ----------------------------
INSERT INTO `course` VALUES (26, 'DFFA23', '操作系统', '2019-06-26 16:10:47');
INSERT INTO `course` VALUES (27, '23FFAA', '数据结构', '2019-06-26 16:11:03');
INSERT INTO `course` VALUES (28, '343FFF', '计算机网络', '2019-06-27 16:11:18');
INSERT INTO `course` VALUES (29, 'FDFF23', '计算机组成原理', '2019-06-26 16:11:35');
INSERT INTO `course` VALUES (32, '9A5EFD', '信息安全', '2019-06-26 20:57:09');
INSERT INTO `course` VALUES (33, '241B08', '软件体系结构', '2019-06-26 21:01:03');
INSERT INTO `course` VALUES (34, '9D963A', 'test', '2019-06-26 21:31:00');
INSERT INTO `course` VALUES (35, 'F2000D', '1111', '2019-06-28 14:43:12');
INSERT INTO `course` VALUES (37, '04429F', '222', '2019-07-02 16:10:07');
INSERT INTO `course` VALUES (38, '52784E', '222', '2020-07-04 22:26:39');

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
-- Records of course_student
-- ----------------------------
INSERT INTO `course_student` VALUES (28, 10, '2019-06-28 13:40:18');
INSERT INTO `course_student` VALUES (29, 10, '2019-06-28 14:37:52');
INSERT INTO `course_student` VALUES (33, 10, '2019-06-28 14:07:31');
INSERT INTO `course_student` VALUES (34, 10, '2019-06-28 13:49:27');
INSERT INTO `course_student` VALUES (35, 10, '2019-06-28 14:43:21');
INSERT INTO `course_student` VALUES (35, 15, '2019-06-30 15:01:49');
INSERT INTO `course_student` VALUES (35, 26, '2019-07-02 16:07:49');

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
-- Records of course_teacher
-- ----------------------------
INSERT INTO `course_teacher` VALUES (26, 11);
INSERT INTO `course_teacher` VALUES (27, 11);
INSERT INTO `course_teacher` VALUES (28, 11);
INSERT INTO `course_teacher` VALUES (29, 11);
INSERT INTO `course_teacher` VALUES (32, 11);
INSERT INTO `course_teacher` VALUES (33, 11);
INSERT INTO `course_teacher` VALUES (34, 11);
INSERT INTO `course_teacher` VALUES (35, 11);
INSERT INTO `course_teacher` VALUES (38, 11);
INSERT INTO `course_teacher` VALUES (37, 27);

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
-- Records of notice
-- ----------------------------
INSERT INTO `notice` VALUES (7, 34, '今天中文检查课设', '<p>今天中文检查课设</p><p>请及时到场</p><p>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 罗辑老师<br></p>', 11, '2019-06-27 18:01:36', '2019-06-27 18:01:36');
INSERT INTO `notice` VALUES (11, 34, 'Java交作业啊', '<p>&nbsp; &nbsp;&nbsp;<b><span lang=\"en\">Java</span></b>是一种广泛使用的计算机<a href=\"https://zh.wikipedia.org/wiki/%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E8%AA%9E%E8%A8%80\" title=\"编程语言\">编程语言</a>，拥有<a href=\"https://zh.wikipedia.org/wiki/%E8%B7%A8%E5%B9%B3%E5%8F%B0\" title=\"跨平台\">跨平台</a>、<a href=\"https://zh.wikipedia.org/wiki/%E7%89%A9%E4%BB%B6%E5%B0%8E%E5%90%91\" title=\"面向对象\">面向对象</a>、<a href=\"https://zh.wikipedia.org/wiki/%E6%B3%9B%E5%9E%8B%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88\" title=\"泛型编程\">泛型编程</a>的特性，广泛应用于企业级Web应用开发和移动应用开发。</p><p>&nbsp;&nbsp;&nbsp;&nbsp;任职于<a href=\"https://zh.wikipedia.org/wiki/%E6%98%87%E9%99%BD%E9%9B%BB%E8%85%A6\" title=\"太阳微系统\">太阳微系统</a>的<a href=\"https://zh.wikipedia.org/wiki/%E8%A9%B9%E5%A7%86%E6%96%AF%C2%B7%E9%AB%98%E6%96%AF%E6%9E%97\" title=\"詹姆斯·高斯林\">詹姆斯·高斯林</a>等人于1990年代初开发Java语言的雏形，最初被命名为Oak，目标设置在<a href=\"https://zh.wikipedia.org/wiki/%E5%AE%B6%E7%94%A8%E7%94%B5%E5%99%A8\" title=\"家用电器\">家用电器</a>等小型系统的<a href=\"https://zh.wikipedia.org/wiki/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80\" title=\"编程语言\">编程语言</a>，应用在<a href=\"https://zh.wikipedia.org/wiki/%E7%94%B5%E8%A7%86%E6%9C%BA\" title=\"电视机\">电视机</a>、<a href=\"https://zh.wikipedia.org/wiki/%E7%94%B5%E8%AF%9D\" title=\"电话\">电话</a>、<a href=\"https://zh.wikipedia.org/wiki/%E9%97%B9%E9%92%9F\" title=\"闹钟\">闹钟</a>、<a href=\"https://zh.wikipedia.org/wiki/%E7%83%A4%E9%9D%A2%E5%8C%85%E6%9C%BA\" title=\"烤面包机\">烤面包机</a>等家用电器的控制和通信。由于这些<a href=\"https://zh.wikipedia.org/w/index.php?title=%E6%99%BA%E8%83%BD%E5%8C%96&amp;action=edit&amp;redlink=1\" title=\"智能化（页面不存在）\">智能化</a>家电的市场需求没有预期的高，Sun公司放弃了该项计划。随着1990年代<a href=\"https://zh.wikipedia.org/wiki/%E7%B6%B2%E9%9A%9B%E7%B6%B2%E8%B7%AF\" title=\"互联网\">互联网</a>的发展，Sun公司看见Oak在<a href=\"https://zh.wikipedia.org/wiki/%E7%B6%B2%E9%9A%9B%E7%B6%B2%E8%B7%AF\" title=\"互联网\">互联网</a>上应用的前景，于是改造了Oak，于1995年5月以Java的名称正式发布。Java伴随着互联网的迅猛发展而发展，逐渐成为重要的网络编程语言。</p><p>&nbsp;&nbsp;&nbsp;&nbsp;Java编程语言的风格十分接近<a href=\"https://zh.wikipedia.org/wiki/C%2B%2B\" title=\"C++\">C++</a>语言。继承了C++语言面向对象技术的核心，舍弃了容易引起错误的<a href=\"https://zh.wikipedia.org/wiki/%E6%8C%87%E9%92%88_(%E4%BF%A1%E6%81%AF%E5%AD%A6)\" title=\"指针 (信息学)\">指针</a>，以<a href=\"https://zh.wikipedia.org/wiki/%E5%8F%83%E7%85%A7\" title=\"引用\">引用</a>取代；移除了C++中的<a href=\"https://zh.wikipedia.org/wiki/%E8%BF%90%E7%AE%97%E7%AC%A6%E9%87%8D%E8%BD%BD\" title=\"运算符重载\">运算符重载</a>和<a href=\"https://zh.wikipedia.org/wiki/%E7%BB%A7%E6%89%BF_(%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%A7%91%E5%AD%A6)\" title=\"继承 (计算机科学)\">多重继承</a>特性，用<a href=\"https://zh.wikipedia.org/wiki/%E6%8E%A5%E5%8F%A3_(Java)\" title=\"接口 (Java)\">接口</a>取代；增加<a href=\"https://zh.wikipedia.org/wiki/%E5%9E%83%E5%9C%BE%E5%9B%9E%E6%94%B6_(%E8%A8%88%E7%AE%97%E6%A9%9F%E7%A7%91%E5%AD%B8)\" title=\"垃圾回收 (计算机科学)\">垃圾回收器</a>功能。在Java SE 1.5版本中引入了<a href=\"https://zh.wikipedia.org/wiki/%E6%B3%9B%E5%9E%8B\" title=\"泛型\">泛型编程</a>、<a href=\"https://zh.wikipedia.org/wiki/%E7%B1%BB%E5%9E%8B%E5%AE%89%E5%85%A8\" title=\"类型安全\">类型安全</a>的枚举、不定长参数和自动装/拆箱特性。太阳微系统对Java语言的解释是：“Java编程语言是个简单、面向对象、分布式、解释性、健壮、安全与系统无关、可移植、高性能、多线程和动态的语言”</p><p>&nbsp;&nbsp;&nbsp;&nbsp;Java不同于一般的<a href=\"https://zh.wikipedia.org/wiki/%E7%B7%A8%E8%AD%AF%E8%AA%9E%E8%A8%80\" title=\"编译语言\">编译语言</a>或<a href=\"https://zh.wikipedia.org/wiki/%E7%9B%B4%E8%AD%AF%E8%AA%9E%E8%A8%80\" title=\"解释型语言\">解释型语言</a>。它首先将源代码编译成<a href=\"https://zh.wikipedia.org/wiki/%E5%AD%97%E8%8A%82%E7%A0%81\" title=\"字节码\">字节码</a>，再依赖各种不同平台上的虚拟机来解释执行字节码，从而具有“<a href=\"https://zh.wikipedia.org/wiki/%E4%B8%80%E6%AC%A1%E7%BC%96%E5%86%99%EF%BC%8C%E5%88%B0%E5%A4%84%E8%BF%90%E8%A1%8C\" title=\"一次编写，到处运行\">一次编写，到处运行</a>”的跨平台特性。在早期JVM中，这在一定程度上降低了Java程序的运行效率。但在J2SE1.4.2发布后，Java的运行速度有了大幅提升。</p><p>&nbsp;&nbsp;&nbsp;&nbsp;与传统类型不同，Sun公司在推出Java时就将其作为开放的技术。全球的Java开发公司被要求所设计的Java软件必须相互兼容。“Java语言靠群体的力量而非公司的力量”是Sun公司的口号之一，并获得了广大软件开发商的认同。这与<a href=\"https://zh.wikipedia.org/wiki/%E5%BE%AE%E8%BD%AF\" title=\"微软\">微软</a>公司所倡导的注重精英和封闭式的模式完全不同，此外，<a href=\"https://zh.wikipedia.org/wiki/%E5%BE%AE%E8%BD%AF%E5%85%AC%E5%8F%B8\" title=\"微软公司\">微软公司</a>后来推出了与之竞争的<a href=\"https://zh.wikipedia.org/wiki/.NET_Framework\" title=\".NET Framework\">.NET平台</a>以及模仿Java的<a href=\"https://zh.wikipedia.org/wiki/C%EF%BC%83\" title=\"C＃\">C#</a>语言。后来Sun公司被<a href=\"https://zh.wikipedia.org/wiki/%E7%94%B2%E9%AA%A8%E6%96%87%E5%85%AC%E5%8F%B8\" title=\"甲骨文公司\">甲骨文公司</a>并购，Java也随之成为甲骨文公司的产品。</p><p>&nbsp;&nbsp;&nbsp;&nbsp;现时，移动<a href=\"https://zh.wikipedia.org/wiki/%E4%BD%9C%E6%A5%AD%E7%B3%BB%E7%B5%B1\" title=\"操作系统\">操作系统</a><a href=\"https://zh.wikipedia.org/wiki/Android\" title=\"Android\">Android</a>大部分的代码采用Java<a href=\"https://zh.wikipedia.org/wiki/%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E8%AA%9E%E8%A8%80\" title=\"编程语言\">编程语言</a>编程。</p><pre><code>import java.util.UUID;<br><br>public class GenerateCode {<br>    public static String generate() {<br>        String code;<br>        UUID uuid = UUID.randomUUID();<br>        code = uuid.toString().substring(0, 6).toUpperCase();<br>        return code;<br>    }<br><br>    public static void main(String[] args) {<br>        for (int i = 0; i &lt; 10; i++)<br>            System.out.println(GenerateCode.generate());<br>    }<br>}</code></pre><p><br></p>', 11, '2019-06-27 20:13:51', '2019-06-27 20:13:51');
INSERT INTO `notice` VALUES (20, 28, '测试', '<p>测试测试测试测试测试测试测试 测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试&nbsp;</p><p><br></p><p>测试测试测试测试测试测试测试 测试测试测试测试测试测试测试</p><p>&nbsp;测试测试测试测试测试测试测试 测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试&nbsp;</p><p><br></p><p>测试测试测试测试测试测试测试 测试测试测试测试测试测试测试</p><p>&nbsp;测试测试测试测试测试测试测试 测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试&nbsp;</p><p><br></p><p>测试测试测试测试测试测试测试 测试测试测试测试测试测试测试</p><p>&nbsp;</p>', 11, '2019-06-28 08:34:54', '2019-06-28 08:34:54');
INSERT INTO `notice` VALUES (22, 35, '测试代码', '<p>测试 测试</p><p>测试测测试</p><pre><code>private final StuCourseMapper stuCourseMapper;<br><br>    @Autowired<br>    public StuCourseListServiceImpl(StuCourseMapper stuCourseMapper) {<br>        this.stuCourseMapper = stuCourseMapper;<br>    }<br><br><br>    public List&lt;StuCourse&gt; findSCourses(User user) {<br>        List&lt;StuCourse&gt; stuCourses = stuCourseMapper.selectByStudentId(user.getId());<br><br>        for (StuCourse stuCourse : stuCourses) {<br>            stuCourse.setStudentCount(stuCourseMapper.selectStudentCount(stuCourse.getId()));<br>            stuCourse.setTeacher(stuCourseMapper.selectTeacherByCourseId(stuCourse.getId()));<br>        }<br><br>        return stuCourses;<br>    }<br><br>    public int enterCourse(StuCourse course, User student) {<br>        StuCourse old = stuCourseMapper.selectByCode(course.getCode());<br>        if (old == null)<br>            return ENTER_COURSE_NOT_EXISTS;<br>        course.setId(old.getId());<br>        course.setName(old.getName());<br>        if (stuCourseMapper.selectEnterTimeByStudentId(course.getId(), student.getId()) != null)<br>            return ENTER_HAS_ENTERED;<br>        boolean ret = stuCourseMapper.insertCourseStudent(course.getId(), student.getId(), course.getEnterTime()) &gt; 0;<br>        if (ret)<br>            return ENTER_SUCC;<br>        else<br>            return ENTER_FAIL;<br>    }</code></pre><p><br></p>', 11, '2019-06-28 15:10:23', '2019-06-28 15:10:23');

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
-- Records of resource
-- ----------------------------

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
-- Records of task
-- ----------------------------

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
-- Records of task_file
-- ----------------------------

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

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (10, 'gt110@qq.com', '123456', 's', '高天', '20161603013', '河南工业大学', '信息科学与工程学院', '软件工程', '软件1601');
INSERT INTO `user` VALUES (11, 'teacher@qq.com', '123456', 't', '罗辑', '', '', '', '', '');
INSERT INTO `user` VALUES (15, 'test@qq.com', '123456', 's', '测试学生', '', '', '', '', '');
INSERT INTO `user` VALUES (26, '111@qq.com', '111111', 's', '111', '', '', '', '', '');
INSERT INTO `user` VALUES (27, '222@qq.com', '222222', 't', '222', '', '', '', '', '');
INSERT INTO `user` VALUES (28, 'test22@qq.com', '12343', 's', 'test', '', '', '', '', '');

SET FOREIGN_KEY_CHECKS = 1;
