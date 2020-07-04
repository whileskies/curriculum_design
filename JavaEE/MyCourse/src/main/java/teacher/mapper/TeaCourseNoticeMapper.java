package teacher.mapper;

import teacher.pojo.TeaNotice;

import java.util.List;

public interface TeaCourseNoticeMapper {
    List<TeaNotice> selectAllByCourseId(Integer courseId);

    int insertNotice(TeaNotice teaNotice);

    int deleteNotice(Integer noticeId);
}
