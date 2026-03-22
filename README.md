# 🎵 AuraBeat - Hệ thống Gợi ý Âm nhạc (Audio Interest Recommendation System)

Chào mừng đến với repository của AuraBeat! Đây là một công cụ gợi ý âm nhạc viết bằng C, tiến hành đọc và phân tích dữ liệu từ một bộ dataset trên Kaggle gồm 686 bài hát để tạo ra các playlist tùy chỉnh dựa trên tâm trạng người dùng (Happy, Sad, Energetic, Calm).

## ⚠️ Quy định & Quy trình làm việc nhóm với Git (Team Git Workflow)

Để giữ cho source code của chúng ta luôn an toàn và tránh việc ghi đè làm mất code của người khác, mọi người vui lòng tuân thủ nghiêm ngặt các quy tắc phân nhánh (branching) sau đây:

### 1. Nguyên tắc vàng: KHÔNG BAO GIỜ push trực tiếp lên nhánh `main`!
Nhánh `main` là phiên bản dự án chính thức và ổn định nhất. Code nằm trên `main` đồng nghĩa với việc đã được test 100% và hoạt động không có lỗi. Chúng ta CHỈ cập nhật nhánh `main` thông qua các "Pull Requests" chính thức.

### 2. Làm việc trên nhánh (branch) riêng của bạn
Mỗi người phải viết code trên một nhánh làm việc riêng biệt của mình (ví dụ: `hoang-branch`, `duy-branch`). 
* Trước khi bắt đầu code mỗi ngày, hãy mở GitHub Desktop và nhấn nút **Fetch origin** để đảm bảo code trên máy bạn được cập nhật mới nhất từ cloud.
* Đảm bảo rằng mục **Current branch** (Nhánh hiện tại) đang được chọn đúng tên nhánh của bạn.

### 3. Không đụng vào nhánh của người khác!
Không commit hay push code lên nhánh cá nhân của thành viên khác. Ví dụ: Nếu bạn đang ngồi trên máy của Hoàng, hoặc đang ở nhánh của Hoàng, và bạn push code thử nghiệm của mình lên, nó sẽ ghi đè lên toàn bộ tiến độ của cậu ấy. Hãy chỉ làm việc trong không gian của riêng mình!

### 4. Cách gộp code (Merge code)
Khi tính năng bạn đảm nhiệm đã hoàn thiện và chạy tốt trên nhánh của bạn, hãy báo cho nhóm biết. Chúng ta sẽ mở một "Pull Request" trên GitHub để review và gộp code từ nhánh của bạn vào nhánh `main` một cách an toàn.

---
**Các tính năng hiện tại (Current Features):**
* Menu tương tác cho người dùng bằng số (Integer-based menu).
* Tách chuỗi CSV nâng cao bằng `strtok` cho 19 cột dữ liệu.
* Lọc bài hát theo tâm trạng không phân biệt chữ hoa/thường (Case-insensitive filtering).
* Ứng dụng thuật toán Fisher-Yates để xáo trộn và tạo playlist ngẫu nhiên.