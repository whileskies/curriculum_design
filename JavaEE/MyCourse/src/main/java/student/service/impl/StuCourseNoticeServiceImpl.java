package student.service.impl;

import login.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import student.mapper.StuCourseNoticeMapper;
import student.pojo.StuCourse;
import student.pojo.StuNotice;
import student.service.StuCourseNoticeService;
import util.Html2Text;

import java.text.SimpleDateFormat;
import java.util.List;

@Service
public class StuCourseNoticeServiceImpl implements StuCourseNoticeService {
    private final StuCourseNoticeMapper stuCourseNoticeMapper;
    private final UserMapper userMapper;


    @Autowired
    public StuCourseNoticeServiceImpl(StuCourseNoticeMapper stuCourseNoticeMapper, UserMapper userMapper) {
        this.stuCourseNoticeMapper = stuCourseNoticeMapper;
        this.userMapper = userMapper;
    }


    public List<StuNotice> findNotices(StuCourse stuCourse) {
        List<StuNotice> stuNotices = stuCourseNoticeMapper.selectAllByCourseId(stuCourse.getId());

        for (StuNotice stuNotice : stuNotices) {
            stuNotice.setPlainTextContent(Html2Text.StripHT(stuNotice.getContent(), 100));

            SimpleDateFormat f = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
            stuNotice.sethUpdateTime(f.format(stuNotice.getUpdateTime()));
            stuNotice.setTeacher(userMapper.selectById(stuNotice.getWriterId()));
        }

        return stuNotices;
    }

}
