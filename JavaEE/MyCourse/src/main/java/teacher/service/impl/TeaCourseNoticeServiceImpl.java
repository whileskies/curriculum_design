package teacher.service.impl;

import login.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import teacher.mapper.TeaCourseNoticeMapper;
import teacher.pojo.TeaCourse;
import teacher.pojo.TeaNotice;
import teacher.service.TeaCourseNoticeService;
import util.Html2Text;

import java.text.SimpleDateFormat;
import java.util.List;

@Service
public class TeaCourseNoticeServiceImpl implements TeaCourseNoticeService {
    private final TeaCourseNoticeMapper teaCourseNoticeMapper;

    private final UserMapper userMapper;

    @Autowired
    public TeaCourseNoticeServiceImpl(TeaCourseNoticeMapper teaCourseNoticeMapper, UserMapper userMapper) {
        this.teaCourseNoticeMapper = teaCourseNoticeMapper;
        this.userMapper = userMapper;
    }


    public List<TeaNotice> findNotices(TeaCourse teaCourse) {
        List<TeaNotice> teaNotices = teaCourseNoticeMapper.selectAllByCourseId(teaCourse.getId());

        for (TeaNotice teaNotice : teaNotices) {
            teaNotice.setPlainTextContent(Html2Text.StripHT(teaNotice.getContent(), 100));

            SimpleDateFormat f = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            teaNotice.sethUpdateTime(f.format(teaNotice.getUpdateTime()));
            teaNotice.setTeacher(userMapper.selectById(teaNotice.getWriterId()));
        }

        return teaNotices;
    }

    public boolean addNotice(TeaNotice teaNotice) {
        return teaCourseNoticeMapper.insertNotice(teaNotice) > 0;
    }

    public boolean deleteNotice(TeaNotice teaNotice) {
        return teaCourseNoticeMapper.deleteNotice(teaNotice.getId()) > 0;
    }
}
