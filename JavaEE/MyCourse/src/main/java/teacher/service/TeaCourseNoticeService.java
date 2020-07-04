package teacher.service;

import teacher.pojo.TeaCourse;
import teacher.pojo.TeaNotice;

import java.util.List;

public interface TeaCourseNoticeService {

    /**
     * 获取课程所有通知
     * @param teaCourse 课程对象
     * @return 通知集合
     */
    List<TeaNotice> findNotices(TeaCourse teaCourse);

    /**
     * 增加公告
     * @param teaNotice 公告
     * @return 是否成功
     */
    boolean addNotice(TeaNotice teaNotice);


    /**
     * 删除公告
     * @param teaNotice 公告对象
     * @return 是否成功删除
     */
    boolean deleteNotice(TeaNotice teaNotice);

}
